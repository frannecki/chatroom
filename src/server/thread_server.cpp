#include "server/thread_server.h"
#include "server/thread_pool.h"

thread_server::thread_server(){}

bool thread_server::init(const std::string& addr_srv, const std::string& port_srv){

    const char* host = "localhost";
    const char* user = "fran";
    const char* passwd = "chjiw";
    const char* db = "db1";
    unsigned int mysql_port = 3306;

    if(sql_task.init(host, user, passwd, db, mysql_port) != CONNECTION_ESTABLISHED){
        outputLog("[ERROR] Failed to connect to MySQL database!");
        return false;
    }
    else outputLog("[INFO] Connected to MySQL database.");

#ifdef MSGCACHE
    const char* host_redis = "127.0.0.1";
    unsigned int port_redis = 6379;
    if(redis_task.init(host_redis, port_redis) != REDIS_CONNECTION_ESTABLISHED){
        outputLog("[ERROR] Failed to connect to Redis database!");
        return false;
    }
    else outputLog("[INFO] Connected to Redis database.");
#else
    outputLog("[INFO] Redis message cache is off.");
#endif

    if((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        outputLog(std::string("[ERROR] Opening socket."));
        return false;
    }
    int port;
    sscanf(port_srv.c_str(), "%d", &port);
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    inet_aton(addr_srv.c_str(), &addr_server.sin_addr);
    bzero(&(addr_server.sin_zero), sizeof(addr_server.sin_zero) / sizeof(addr_server.sin_zero[0]));
    printf("[INFO] IP: %s; Port: %d.\n", addr_srv.c_str(), port);
    if(bind(socket_server, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0){
        perror("[ERROR] Binding");
        outputLog(std::string("[ERROR] Binding socket."));
        return false;
    }
    if(listen(socket_server, 20) < 0){
        outputLog(std::string("[ERROR] Listening."));
        return false;
    }
    cntfd = 0;
    
    // create another socket and connect to socket_server as a stopper
    if((socket_stopper_client = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        return false;
    }
    else{
        printf("[INFO] socket_stopper_client: %d.\n", socket_stopper_client);
    }
    connThread = boost::thread(thread_server::connectStopper, (void*)this);
    socklen_t size = sizeof(addr_client);
    if((socket_stopper = accept(socket_server, (struct sockaddr*)&addr_server, &size)) < 0){
        return false;
    }
    else  printf("[INFO]socket server: %d; socket_stopper: %d.\n", socket_server, socket_stopper);
    connThread.join();

    outputLog("[INFO] Server initialized.");
    
    workerThread = boost::thread(thread_server::loopTask, (void*)this);
    
    return true;
}

thread_server::~thread_server(){
    printf("[INFO] Main thread finished.\n");
}

void thread_server::closeAll(){
    {
        boost::unique_lock<boost::shared_mutex> locker(mutexRunning);
        is_Running = false;
    }
    send(socket_stopper_client, "stop", 10, 0);
    workerThread.join();
    for(int i = 0; i < cntfd; ++i){
        close(uIDs[i].sockfd);
    }
    close(socket_stopper);
    close(socket_stopper_client);
    close(socket_server);
}

void thread_server::outputLog(const std::string& logcont){
    log_model.insertRows(log_model.rowCount(),1);
    std::stringstream log_model_msg;
    log_model_msg << logcont.c_str();
    QVariant new_row(QString(log_model_msg.str().c_str()));
    log_model.setData(log_model.index(log_model.rowCount()-1), new_row);
    emit logUpdated();
}

void thread_server::connectStopper(void* param){
    thread_server* th = (thread_server*)param;
    ::connect(th->socket_stopper_client, (struct sockaddr*)&(th->addr_server), sizeof(th->addr_server));
}

void thread_server::loopTask(void* param){
    thread_server* th = (thread_server*)param;
    {
        boost::unique_lock<boost::shared_mutex> locker(th->mutexRunning);
        th->is_Running = true;
    }
    th->outputLog(std::string("[INFO] Listening..."));
    std::string str;
    int recvLen;
    char buff[MAXBUFFLEN];
    bzero(buff, MAXBUFFLEN);
    typeMsg msg_;
    int maxsock = std::max(th->socket_server, th->socket_stopper);
    
    ThreadPool msg_threadpool(20);

    epoll_event ev, events[MAXUSERNUM+2], ev_stopper;
    th->epfd = epoll_create1(0);
    if(th->epfd == -1){
        perror("[ERROR] epoll_create1()");
        exit(EXIT_FAILURE);
    }
    ev.events = EPOLLIN;
    ev.data.fd = th->socket_server;
    ev_stopper.events = EPOLLIN;
    ev_stopper.data.fd = th->socket_stopper;
    epoll_ctl(th->epfd, EPOLL_CTL_ADD, th->socket_server, &ev);
    epoll_ctl(th->epfd, EPOLL_CTL_ADD, th->socket_stopper, &ev_stopper);

    bool threadStopping = false;
    while(1){
        for(int i = 0; i < MAXUSERNUM; ++i){
            if(th->uIDs[i].sockfd > maxsock)  maxsock = th->uIDs[i].sockfd;
        }
        int num_evfd = epoll_wait(th->epfd, events, MAXUSERNUM, -1);
        for(int n = 0; n < num_evfd; ++n){
            int evfd = events[n].data.fd;
            if(evfd == th->socket_stopper){
                recv(th->socket_stopper, buff, MAXBUFFLEN, 0);
                boost::shared_lock<boost::shared_mutex> locker(th->mutexRunning);
                if(!th->is_Running){
                    threadStopping = true;
                    break;
                }
            }
            else if(evfd == th->socket_server){
                socklen_t size = sizeof(th->addr_client);
                th->outputLog(std::string("[INFO] Waiting for client to connect..."));
                if((th->socket_client = accept(th->socket_server, (struct sockaddr*)&(th->addr_server), &size)) < 0){
                    continue;
                }
                th->outputLog(std::string("[INFO] New client accepted."));
            
                if(th->cntfd < MAXUSERNUM){
                    //usleep(100000);
                    bzero(buff, strlen(buff));
                    recvLen = recv(th->socket_client, buff, MAXBUFFLEN, 0);
                    if(recvLen < 0){
                        th->outputLog(std::string("[ERROR] recv() error! Closing client..."));
                        perror("[ERROR] recv()");
                        close(th->socket_client);
                    }
                    else if(recvLen == 0){
                        th->outputLog(std::string("[ERROR] Invalid username! Closing client..."));
                        close(th->socket_client);
                    }
                    else{
                        char username[15], password[20], tmpbuf[15];
                        int request_code = 0;
                        sscanf(buff, "%s %d %s", username, &request_code, password);
                        if(th->contacts.count(std::string(username)) > 0){
                            th->outputLog(std::string("[ERROR] Clients with the same username! Closing client..."));
                            composeMsg(buff, "server", SERVER_FEEDBACK, "Connection Rejected!");
                            if(send(th->socket_client, buff, strlen(buff), 0) >= 0){
                                th->outputLog(std::string("[INFO] Rejection issued"));
                            }
                            else  th->outputLog(std::string("[ERROR] Rejection not issued"));
                            close(th->socket_client);
                        }
                        else if(request_code == CLIENT_LOGIN){
                            // query username in database;
                            unsigned int result_code = th->sql_task.loginUser(username, password);
                            if(LOGIN_VALID == result_code){
                                th->outputLog(std::string("[INFO] New client is #") + std::to_string(th->socket_client) + " " + std::string(username));
                                {
                                    boost::unique_lock<boost::shared_mutex> locker(th->mutexUIds);
                                th->uIDs[th->cntfd++].sockfd = th->socket_client;
                                th->uIDs[th->cntfd-1].ev.events = EPOLLIN;
                                th->uIDs[th->cntfd-1].ev.data.fd = th->socket_client;
                                th->uIDs[th->cntfd-1].uname = std::string(username);
                                th->contacts.insert(std::pair<std::string, int>(th->uIDs[th->cntfd-1].uname, th->cntfd-1));
                                th->contacts_ind.insert(std::pair<int, int>(th->socket_client, th->cntfd-1));
                                }
                                epoll_ctl(th->epfd, EPOLL_CTL_ADD, th->socket_client, &(th->uIDs[th->cntfd-1].ev));
                        
                                composeMsg(buff, "server", SERVER_FEEDBACK, "Connection Established.");
                                send(th->socket_client, buff, strlen(buff), 0);
                                // retrieve pending messages from redis
#ifdef MSGCACHE
                                int num_messages = th->redis_task.getNumMsg(username);
                                for(int idx_msg = 0; idx_msg < num_messages; ++idx_msg){
                                    const char* buf = th->redis_task.retrieveMsg();
                                    if(msg_.btype == MESSAGE){
                                        send(th->socket_client, buf, strlen(buf), 0);
                                    }
                                }
#endif
                            }
                            else{
                                th->outputLog("[ERROR] Invalid username or password! Closing client...");
                                composeMsg(buff, "server", SERVER_FEEDBACK, "Login Failed.");
                                if(send(th->socket_client, buff, strlen(buff), 0) >= 0){
                                    th->outputLog(std::string("[INFO] Rejection issued"));
                                }
                                else  th->outputLog(std::string("[ERROR] Rejection not issued"));
                                close(th->socket_client);
                            }
                        }
                        else if(request_code == CLIENT_REGISTER){
                            // insert user to db table;
                            if(REGISTERED == th->sql_task.insertUser(username, password)){
                                composeMsg(buff, "server", SERVER_FEEDBACK, "Registration Succeeded.");
                                th->outputLog(std::string("[INFO] Registration Succeeded."));
                                send(th->socket_client, buff, strlen(buff), 0);
                            }
                            else{
                                composeMsg(buff, "server", SERVER_FEEDBACK, "Registration Failed.");
                                th->outputLog(std::string("[ERROR] Registration Failed!"));
                                send(th->socket_client, buff, strlen(buff), 0);
                            }
                            th->outputLog("[INFO] Closing socket...");
                            close(th->socket_client);
                        }
                        else{
                            composeMsg(buff, "server", SERVER_FEEDBACK, "Undefined Request.");
                            send(th->socket_client, buff, strlen(buff), 0);
                            th->outputLog("[ERROR] Unrecognized request code " + std::to_string(request_code));
                            close(th->socket_client);
                            continue;
                        }
                    }
                }
                else{
                    th->outputLog(std::string("[ERROR] Exceeded the maximum connections!"));
                    composeMsg(buff, std::string("server"), SERVER_FEEDBACK, "Connection Rejected!");
                    if(send(th->socket_client, buff, strlen(buff), 0) >= 0){
                        th->outputLog(std::string("[INFO] Rejection issued"));
                    }
                    else  th->outputLog(std::string("[ERROR] Rejection not issued"));
                }
            }
            else if(th->contacts_ind.count(evfd) > 0){
                int i = th->contacts_ind[evfd];
                bzero(buff, strlen(buff));
                recvLen = recv(th->uIDs[i].sockfd, buff, MAXBUFFLEN, 0);
                if(recvLen < 0){
                    th->outputLog(std::string("[Error] recv() failed!"));
                    th->clrsocket(i);
                }
                if(recvLen == 0)  continue;
                else{
                    parseSMsg(buff, msg_);
                    th->outputLog("[INFO] Forwarding message from " + 
                              th->uIDs[i].uname + " to " + 
                              std::string(msg_.sock_dest) + "...");
                    
                    if(msg_.btype == CLIENT_LOGOUT){
                        th->outputLog("[INFO] Client logout requested.");
                        composeMsg(buff, "server", SERVER_FEEDBACK, "Logout Accepted.");
                        send(th->uIDs[i].sockfd, buff, strlen(buff), 0);
                        th->clrsocket(i);
                    }
                    else if(msg_.btype == USER_SEARCH){
                        char users[100] = {'\0'};
                        MYSQL_RES* res;
                        if(strlen(msg_.msg) > 0 && th->sql_task.queryUser(msg_.msg) == USER_VALID
                            && (res = th->sql_task.getResult()))
                        {
                            for(int i = 0; i < mysql_num_rows(res); ++i){
                                MYSQL_ROW row = mysql_fetch_row(res);
                                if(strlen(users) + strlen(row[1]) + 1 >= 100)  break;
                                strcat(users, " ");
                                strcat(users, row[1]);
                            }
                        }
                        composeMsg(buff, "server", SERVER_QUERY, users);
                        printf("[INFO] Back to %s\n", th->uIDs[i].uname.c_str());
                        send(th->uIDs[i].sockfd, buff, strlen(buff), 0);
                    }
                    else if(msg_.btype == USER_SELECTION){
                        //TODO;
                    }
                    else  msg_threadpool.getTask(forwardGroupMsg, (void*)th, i, msg_);
                }
            }
        }
        if(threadStopping)  break;
    }
}

void thread_server::forwardGroupMsg(void* ptr, int sender,
                             const typeMsg &msg_){
    
    thread_server *ts = (thread_server*)ptr;
    boost::shared_lock<boost::shared_mutex> locker(ts->mutexUIds);
    if(msg_.msg[0] == '\0')  return;
    char buffer[MAXBUFFLEN];
    bzero(buffer, strlen(buffer));
    composeMsg(buffer, ts->uIDs[sender].uname, msg_.btype, msg_.msg);
    if(0 == strcmp(msg_.sock_dest, "All")){
        for(int i = 0; i < ts->cntfd; ++i){
            if(i != sender)
                send(ts->uIDs[i].sockfd, buffer, strlen(buffer), 0);
        }
    }
    else{
        if(ts->contacts.count(std::string(msg_.sock_dest)) == 0){
#ifdef MSGCACHE
            unsigned int result_code = ts->sql_task.queryUser(msg_.sock_dest, false);
            if(USER_VALID == result_code){
                ts->redis_task.cacheMsg(msg_.sock_dest, buffer);
            }
#endif
            return;
        }
        int recver = ts->contacts[std::string(msg_.sock_dest)];
        if(recver == sender)  return;
        if(send(ts->uIDs[recver].sockfd, buffer, strlen(buffer), 0) >= 0){
            ts->outputLog("[INFO] Sending to " + std::string(msg_.sock_dest) + "...");
        }
        else{
            ts->outputLog("[ERROR] Sending failed. Closing client " + std::string(msg_.sock_dest));
            ts->clrsocket(recver);
            close(ts->uIDs[recver].sockfd);
        }
    }
}

void thread_server::clrsocket(int idx){
    if(idx < 0  ||  idx >= cntfd)  return;
    close(uIDs[idx].sockfd);    
    outputLog(std::string("[INFO] Removing client ") + uIDs[idx].uname);
    {
        boost::unique_lock<boost::shared_mutex> locker(mutexUIds);
    contacts_ind.erase(uIDs[idx].sockfd);
    contacts.erase(uIDs[idx].uname);
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[idx].sockfd, &(uIDs[idx].ev));
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[cntfd-1].sockfd, &(uIDs[cntfd-1].ev));
    uIDs[idx] = uIDs[--cntfd];
    if(cntfd > idx){
        contacts[uIDs[idx].uname] = idx;
        contacts_ind[uIDs[idx].sockfd] = idx;
    }
    }
    epoll_ctl(epfd, EPOLL_CTL_ADD, uIDs[idx].sockfd, &(uIDs[idx].ev));
    uIDs[cntfd].reset();
}

QStringListModel* thread_server::logModel(){
    return &log_model;
}

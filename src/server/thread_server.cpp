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
        return false;
    }
    int optval = 1;
    setsockopt(socket_server, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(int));
    int port;
    sscanf(port_srv.c_str(), "%d", &port);
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    inet_aton(addr_srv.c_str(), &addr_server.sin_addr);
    bzero(&(addr_server.sin_zero), sizeof(addr_server.sin_zero) / sizeof(addr_server.sin_zero[0]));
    printf("[INFO] IP: %s; Port: %d.\n", addr_srv.c_str(), port);
    if(bind(socket_server, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0){
        perror("[ERROR] Binding");
        return false;
    }
    if(listen(socket_server, 20) < 0){
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
    else  printf("[INFO] socket server: %d; socket_stopper: %d.\n", socket_server, socket_stopper);
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
        close(uIDs[i].sockfd_file);
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
    std::string str;
    int recvLen;
    char filebuff[MAXFILEBUFFLEN];
    char buff[MAXBUFFLEN];
    usermsg msg_recved;
    usermsg msg_sent;
    bzero(msg_recved.msg, MAXBUFFLEN+1);
    bzero(msg_sent.msg, MAXBUFFLEN+1);
    bzero(buff, MAXBUFFLEN+1);
    int maxsock = std::max(th->socket_server, th->socket_stopper);
    
    ThreadPool msg_threadpool(20);

    epoll_event ev, events[2*MAXUSERNUM+2], ev_stopper;
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
                if((th->socket_client = accept(th->socket_server, (struct sockaddr*)&(th->addr_server), &size)) < 0){
                    continue;
                }
            
                if(th->cntfd < MAXUSERNUM){
                    recvLen = recv(th->socket_client, (char*)&msg_recved, sizeof(msg_recved), 0);
                    if(recvLen < 0){
                        close(th->socket_client);
                    }
                    else if(recvLen == 0){
                        close(th->socket_client);
                    }
                    else{
                        char username[15], password[20], tmpbuf[15];
                        sscanf(msg_recved.msg, "%s %s", username, password);
                        if(CLIENT_FILE_SOCKET == msg_recved.btype){
                            if(th->contacts.count(std::string(username)) > 0){
                                int id = th->contacts[std::string(username)];
                                th->uIDs[id].sockfd_file = th->socket_client;
                                th->uIDs[id].ev_file.events = EPOLLIN;
                                th->uIDs[id].ev_file.data.fd = th->socket_client;
                                epoll_ctl(th->epfd, EPOLL_CTL_ADD, th->socket_client, &(th->uIDs[id].ev_file));
                                th->contacts_file.insert(std::pair<int, int>
                                    (th->uIDs[id].sockfd_file, th->uIDs[id].sockfd));
                                printf("[INFO] client file socket for %s is %d.\n", username, th->socket_client);
                            }
                            else{
                                close(th->socket_client);
                            }
                        }
                        else if(th->contacts.count(std::string(username)) > 0){
                            th->outputLog(std::string("[ERROR] Clients with the same username! Closing client..."));
                            composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Connection Rejected!");
                            if(send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0) >= 0){
                                th->outputLog(std::string("[INFO] Rejection issued"));
                            }
                            close(th->socket_client);
                        }
                        else if(CLIENT_LOGIN == msg_recved.btype){
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
                        
                                composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Connection Established.");
                                send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0);
                                // retrieve pending messages from redis
#ifdef MSGCACHE
                                int num_messages = th->redis_task.getNumMsg(username);
                                for(int idx_msg = 0; idx_msg < num_messages; ++idx_msg){
                                    const char* buf = th->redis_task.retrieveMsg();
                                    composeMsg(msg_sent, (char*)buf);
                                    send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0);
                                }
#endif
                            }
                            else{
                                th->outputLog("[ERROR] Invalid username or password! Closing client...");
                                //printf("Invalid: %s %s %s\n", username, password, msg_recved.msg);
                                composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Login Failed.");
                                if(send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0) >= 0){
                                    th->outputLog(std::string("[INFO] Rejection issued"));
                                }
                                close(th->socket_client);
                            }
                        }
                        else if(CLIENT_REGISTER == msg_recved.btype){
                            // insert user to db table;
                            if(REGISTERED == th->sql_task.insertUser(username, password)){
                                composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Registration Succeeded.");
                                send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0);
                                th->outputLog(std::string("[INFO] Registration Succeeded."));
                            }
                            else{
                                composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Registration Failed.");
                                send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0);
                                th->outputLog(std::string("[ERROR] Registration Failed!"));
                            }
                            close(th->socket_client);
                        }
                        else{
                            composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Undefined Request.");
                            send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0);
                            close(th->socket_client);
                            continue;
                        }
                    }
                }
                else{
                    th->outputLog("[ERROR] Exceeded the maximum connections!");
                    composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Connection Rejected!");
                    if(send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0) >= 0){
                        th->outputLog("[INFO] Rejection issued");
                    }
                }
            }

            else if(th->contacts_ind.count(evfd) > 0){
                int i = th->contacts_ind[evfd];
                recvLen = recv(evfd, (char*)&msg_recved, sizeof(msg_recved), 0);
                if(recvLen < 0){
                    th->clrsocket(i);
                }
                if(recvLen == 0)  continue;
                else{
                    th->outputLog("[INFO] Forwarding message from " + 
                              th->uIDs[i].uname + " to " + 
                              std::string(msg_recved.sock_dest) + "...");
                    
                    if(CLIENT_LOGOUT == msg_recved.btype){
                        th->outputLog("[INFO] Client logout requested.");
                        composeMsg(msg_sent, "server", SERVER_FEEDBACK, "Logout Accepted.");
                        send(th->uIDs[i].sockfd, (char*)&msg_sent, sizeof(msg_sent), 0);
                        th->clrsocket(i);
                    }
                    else if(USER_SEARCH == msg_recved.btype){
                        char users[100] = {'\0'};
                        MYSQL_RES* res;
                        if(strlen(msg_recved.msg) > 0 && th->sql_task.queryUser(msg_recved.msg) == USER_VALID
                            && (res = th->sql_task.getResult()))
                        {
                            for(int i = 0; i < mysql_num_rows(res); ++i){
                                MYSQL_ROW row = mysql_fetch_row(res);
                                if(strlen(users) + strlen(row[1]) + 1 >= 100)  break;
                                strcat(users, row[1]);
                                strcat(users, " ");
                            }
                        }
                        composeMsg(msg_sent, "server", SERVER_QUERY, users);
                        send(th->uIDs[i].sockfd, (char*)&msg_sent, sizeof(msg_sent), 0);
                    }
                    else{
                        if(FILENAME == msg_recved.btype){
                            std::string file_dest(msg_recved.sock_dest);
                            if(th->contacts.count(file_dest)){
                                th->uIDs[i].sockfd_file_dest = th->uIDs[th->contacts[file_dest]].sockfd_file;
                            }
                        }
                        msg_threadpool.getTask(forwardGroupMsg, (void*)th, i, msg_recved);
                    }
                }
            }

            else if(th->contacts_file.count(evfd) > 0 && th->contacts_ind.count(th->contacts_file[evfd]) > 0)
            {
                int flen = recv(evfd, filebuff, MAXFILEBUFFLEN, 0);
                if(flen <= 0)  continue;
                int i = th->contacts_ind[th->contacts_file[evfd]];
                if(th->contacts_file.count(th->uIDs[i].sockfd_file_dest) > 0 && 
                    send(th->uIDs[i].sockfd_file_dest, filebuff, flen, 0) <= 0)
                {
                    perror("[ERROR] transfer file");
                    printf("[ERROR] whose socket is %d\n", th->uIDs[i].sockfd_file_dest);
                }
            }
        }
        if(threadStopping)  break;
    }
}

void thread_server::forwardGroupMsg(void* ptr, int sender, const usermsg &msg_)
{
    
    thread_server *ts = (thread_server*)ptr;
    boost::shared_lock<boost::shared_mutex> locker(ts->mutexUIds);
    if(0 == strlen(msg_.msg))  return;
    
    char buffer[MAXBUFFLEN];
    bzero(buffer, sizeof(buffer));
    composeMsg(buffer, ts->uIDs[sender].uname.c_str(), msg_.btype, msg_.msg);

    usermsg msg_sent;
    composeMsg(msg_sent, ts->uIDs[sender].uname.c_str(), msg_.btype, msg_.msg);
    if(0 == strcmp(msg_.sock_dest, "All")){
        for(int i = 0; i < ts->cntfd; ++i){
            if(i != sender)
                send(ts->uIDs[i].sockfd, (char*)&msg_sent, sizeof(msg_sent), 0);
        }
    }
    else{
        if(msg_.btype == MESSAGE && ts->contacts.count(std::string(msg_.sock_dest)) == 0){
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
        if(send(ts->uIDs[recver].sockfd, (char*)&msg_sent, sizeof(msg_sent), 0) >= 0){
            ts->outputLog("[INFO] Sending to " + std::string(msg_.sock_dest) + "...");
        }
        else{
            ts->clrsocket(recver);
            close(ts->uIDs[recver].sockfd);
        }
    }
}

void thread_server::clrsocket(int idx){
    if(idx < 0  ||  idx >= cntfd)  return;
    close(uIDs[idx].sockfd);
    close(uIDs[idx].sockfd_file); 
    outputLog(std::string("[INFO] Removing client ") + uIDs[idx].uname);
    {
        boost::unique_lock<boost::shared_mutex> locker(mutexUIds);
    contacts_ind.erase(uIDs[idx].sockfd);
    contacts.erase(uIDs[idx].uname);
    contacts_file.erase(uIDs[idx].sockfd_file);
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[idx].sockfd, &(uIDs[idx].ev));
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[idx].sockfd_file, &(uIDs[idx].ev_file));
    uIDs[idx] = uIDs[--cntfd];
    if(cntfd > idx){
        contacts[uIDs[idx].uname] = idx;
        contacts_ind[uIDs[idx].sockfd] = idx;
    }
    }
    uIDs[cntfd].reset();
}

QStringListModel* thread_server::logModel(){
    return &log_model;
}

#include "thread_server.h"
#include "thread_pool.h"

thread_server::thread_server(){}

bool thread_server::init(const std::string& addr_srv, const std::string& port_srv){
    
    mutexRunning = new QMutex();

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
    outputLog(std::string("[INFO] Server initialized."));
    
    return true;
}

thread_server::~thread_server(){
    printf("[INFO] Waiting for main thread to finish...\n");
    terminate();  // take care of this
    QThread::wait();
    printf("[INFO] Main thread finished.\n");
    delete mutexRunning;
}

void thread_server::closeAll(){
    QMutexLocker locker(mutexRunning);
    is_Running = false;
    for(int i = 0; i < cntfd; ++i){
        close(uIDs[i].sockfd);
    }
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

void thread_server::run(){
    loopTask();
}

void thread_server::loopTask(){
    
    is_Running = true;
    outputLog(std::string("[INFO] Listening..."));
    std::string str;
    int recvLen;
    char buff[MAXBUFFLEN];
    bzero(buff, MAXBUFFLEN);
    typeMsg msg_;
    int maxsock = socket_server;
    
    ThreadPool msg_threadpool(20);

    epoll_event ev, events[MAXUSERNUM+1];
    epfd = epoll_create1(0);
    if(epfd == -1){
        perror("epoll_create1()");
        exit(EXIT_FAILURE);
    }
    ev.events = EPOLLIN;
    ev.data.fd = socket_server;
    epoll_ctl(epfd, EPOLL_CTL_ADD, socket_server, &ev);

    while(true){
        for(int i = 0; i < MAXUSERNUM; ++i){
            if(uIDs[i].sockfd > maxsock)  maxsock = uIDs[i].sockfd;
        }
        int num_evfd = epoll_wait(epfd, events, MAXUSERNUM, -1);
        
        for(int n = 0; n < num_evfd; ++n){
            int evfd = events[n].data.fd;
            if(evfd == socket_server){
                socklen_t size = sizeof(addr_client);
                outputLog(std::string("[INFO] Waiting for client to connect..."));
                if((socket_client = accept(socket_server, (struct sockaddr*)&addr_server, &size)) < 0){
                    continue;
                }
                outputLog(std::string("[INFO] New client accepted."));
            
                if(cntfd < MAXUSERNUM){
                    //usleep(100000);
                    bzero(buff, strlen(buff));
                    recvLen = recv(socket_client, buff, MAXBUFFLEN, 0);
                    if(recvLen < 0){
                        outputLog(std::string("[ERROR] recv() error! Closing client..."));
                        perror("[ERROR] recv()");
                        close(socket_client);
                    }
                    else if(recvLen == 0){
                        outputLog(std::string("[ERROR] Invalid username! Closing client..."));
                        close(socket_client);
                    }
                    else{
                        // printf("[INFO] Nickname of client #%d is %s.\n", socket_client, buff);
                        if(contacts.count(std::string(buff)) > 0){
                            outputLog(std::string("[ERROR] Clients with the same username! Closing client..."));
                            buff[0] = '\0';
                            composeMsg(buff, std::string("server"), 3, "Connection Rejected!");
                            if(send(socket_client, buff, strlen(buff), 0) >= 0){
                                outputLog(std::string("[INFO] Rejection issued"));
                            }
                            else outputLog(std::string("[ERROR] Rejection not issued"));
                            close(socket_client);
                        }
                        else{
                            outputLog(std::string("[INFO] New client is #") + std::to_string(socket_client) + std::string(buff) + std::string("."));
                            uIDs[cntfd++].sockfd = socket_client;
                            uIDs[cntfd-1].ev.events = EPOLLIN;
                            uIDs[cntfd-1].ev.data.fd = socket_client;
                            uIDs[cntfd-1].uname = std::string(buff);
                            contacts.insert(std::pair<std::string, int>(uIDs[cntfd-1].uname, cntfd-1));
                            contacts_ind.insert(std::pair<int, int>(socket_client, cntfd-1));
                            epoll_ctl(epfd, EPOLL_CTL_ADD, socket_client, &(uIDs[cntfd-1].ev));
                        
                            buff[0] = '\0';
                            composeMsg(buff, std::string("server"), 3, "Connection Established.");
                            send(socket_client, buff, strlen(buff), 0);
                        }
                    }
                }
                else{
                    outputLog(std::string("[ERROR] Exceeded the maximum connections!"));
                    buff[0] = '\0';
                    composeMsg(buff, std::string("server"), 3, "Connection Rejected!");
                    if(send(socket_client, buff, strlen(buff), 0) >= 0){
                        outputLog(std::string("[INFO] Rejection issued"));
                    }
                    else outputLog(std::string("[ERROR] Rejection not issued"));
                }
            }
            else if(contacts_ind.count(evfd) > 0){
                int i = contacts_ind[evfd];
                bzero(buff, strlen(buff));
                recvLen = recv(uIDs[i].sockfd, buff, MAXBUFFLEN, 0);
                if(recvLen < 0){
                    outputLog(std::string("[Error] recv() failed!"));
                    clrsocket(i);
                }
                if(recvLen == 0)  continue;
                else{
                    parseSMsg(buff, msg_);
                    outputLog(std::string("[INFO] Forwarding message from ") + 
                              uIDs[i].uname + std::string(" to ") + 
                              std::string(msg_.sock_dest) + std::string("..."));
                    
                    if(msg_.btype == CLIENT_LOGOUT){
                        outputLog("[INFO] Client logout requested.");
                        clrsocket(i);
                    }
                    //forwardGroupMsg(maxsock, uIDs[i].sockfd, msg_);
                    else  msg_threadpool.getTask(forwardGroupMsg, this, i, msg_);
                }
            }
        }
        {
            QMutexLocker locker(mutexRunning);
            if(!is_Running)  break;
        }
    }
}

void thread_server::forwardGroupMsg(void* ptr, int sender,
                             const typeMsg &msg_){
    
    thread_server *ts = (thread_server*)ptr;
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
        if(ts->contacts.count(std::string(msg_.sock_dest)) == 0)  return;
        int recver = ts->contacts[std::string(msg_.sock_dest)];
        if(recver == sender)  return;
        if(send(ts->uIDs[recver].sockfd, buffer, strlen(buffer), 0) >= 0){
            ts->outputLog(std::string("[INFO] Sending to ") + std::string(msg_.sock_dest) + std::string("..."));
        }
        else{
            ts->outputLog(std::string("[ERROR] Sending failed. Closing client ") + std::string(msg_.sock_dest));
            ts->clrsocket(recver);
        }
    }
}

void thread_server::clrsocket(int idx){
    if(idx < 0  ||  idx >= cntfd)  return;
    outputLog(std::string("[INFO] Removing client ") + uIDs[idx].uname);
    close(uIDs[idx].sockfd);
    contacts_ind.erase(uIDs[idx].sockfd);
    contacts.erase(uIDs[idx].uname);
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[idx].sockfd, &(uIDs[idx].ev));
    epoll_ctl(epfd, EPOLL_CTL_DEL, uIDs[cntfd-1].sockfd, &(uIDs[cntfd-1].ev));
    uIDs[idx] = uIDs[--cntfd];
    if(cntfd > idx){
        contacts[uIDs[idx].uname] = idx;
        contacts_ind[uIDs[idx].sockfd] = idx;
    }
    epoll_ctl(epfd, EPOLL_CTL_ADD, uIDs[idx].sockfd, &(uIDs[idx].ev));
    uIDs[cntfd].reset();
}

QStringListModel* thread_server::logModel(){
    return &log_model;
}

/*
void thread_server::logUpdated(){}
*/
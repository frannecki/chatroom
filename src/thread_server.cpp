#include "thread_server.h"

thread_server::thread_server(){}

bool thread_server::init(const std::string& addr_srv, const std::string& port_srv){
    
    mutexRunning = new QMutex();
    msg_threadpool.setMaxThreadCount(20);

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
    wait();
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
    while(true){
        FD_ZERO(&fs);
        FD_SET(socket_server, &fs);
        for(int i = 0; i < MAXUSERNUM; ++i){
            if(uIDs[i].sockfd != 0){
                FD_SET(uIDs[i].sockfd, &fs);
                if(uIDs[i].sockfd > maxsock)  maxsock = uIDs[i].sockfd;
            }
        }
        select(maxsock+1, &fs, NULL, NULL, NULL);
        for(int i = 0; i < cntfd; ++i){
            if(FD_ISSET(uIDs[i].sockfd, &fs)){
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
                    else  msg_threadpool.start(new msg_forwarder(maxsock, uIDs[i].sockfd, msg_, this));
                }
            }
        }
        if(FD_ISSET(socket_server, &fs)){
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
                        strcat(buff, "server 3 ");
                        strcat(buff, " Connection Rejected!");
                        if(send(socket_client, buff, strlen(buff), 0) >= 0){
                            outputLog(std::string("[INFO] Rejection issued"));
                        }
                        else outputLog(std::string("[ERROR] Rejection not issued"));
                        close(socket_client);
                    }
                    else{
                        outputLog(std::string("[INFO] New client is #") + std::to_string(socket_client) + std::string(buff) + std::string("."));
                        uIDs[cntfd++].sockfd = socket_client;
                        uIDs[cntfd-1].uname = std::string(buff);
                        contacts.insert(std::pair<std::string, int>(uIDs[cntfd-1].uname, socket_client));
                        contacts_ind.insert(std::pair<int, std::string>(socket_client, uIDs[cntfd-1].uname));
                        
                        buff[0] = '\0';
                        strcat(buff, "server 3 ");
                        strcat(buff, " Connection Established.");
                        send(socket_client, buff, strlen(buff), 0);
                        // parseSMsg(buff, msg_);
                        // forwardGroupMsg(maxsock, socket_client, msg_);
                    }
                }
            }
            else{
                outputLog(std::string("[ERROR] Exceeded the maximum connections!"));
                buff[0] = '\0';
                strcat(buff, "server 3 ");
                strcat(buff, " Connection Rejected!");
                if(send(socket_client, buff, strlen(buff), 0) >= 0){
                    outputLog(std::string("[INFO] Rejection issued"));
                }
                else outputLog(std::string("[ERROR] Rejection not issued"));
            }
        }
        {
            QMutexLocker locker(mutexRunning);
            if(!is_Running)  break;
        }
    }
}

void thread_server::forwardGroupMsg(int cntfd, int sender,
                             const typeMsg &msg_){
    
    if(msg_.msg[0] == '\0')  return;
    char buffer[MAXBUFFLEN];
    bzero(buffer, strlen(buffer));
    strcat(buffer, contacts_ind[sender].c_str());
    strcat(buffer, " ");
    strcat(buffer, std::to_string(msg_.btype).c_str());
    strcat(buffer, " ");
    strcat(buffer, msg_.msg);
    if(0 == strcmp(msg_.sock_dest, "All")){
        for(int i = 0; i < cntfd; ++i){
            if(uIDs[i].sockfd != sender)
                send(uIDs[i].sockfd, buffer, strlen(buffer), 0);
        }
    }
    else{
        if(contacts.count(std::string(msg_.sock_dest)) == 0)  return;
        int recver = contacts[std::string(msg_.sock_dest)];
        if(recver == sender)  return;
        if(send(recver, buffer, strlen(buffer), 0) >= 0){
            outputLog(std::string("[INFO] Sending to ") + std::string(msg_.sock_dest) + std::string("..."));
        }
        else{
            outputLog(std::string("[ERROR] Sending failed. Closing client ") + std::string(msg_.sock_dest));
            int idx = 0;
            for(; idx < cntfd, uIDs[idx].sockfd != recver; ++idx);
            clrsocket(idx);
        }
    }
}

void thread_server::clrsocket(int idx){
    if(idx < 0  ||  idx >= cntfd)  return;
    outputLog(std::string("[INFO] Removing client ") + uIDs[idx].uname);
    close(uIDs[idx].sockfd);
    contacts_ind.erase(uIDs[idx].sockfd);
    contacts.erase(uIDs[idx].uname);
    FD_CLR(uIDs[idx].sockfd, &fs);
                    
    uIDs[idx] = uIDs[--cntfd];
    uIDs[cntfd].reset();
}

QStringListModel* thread_server::logModel(){
    return &log_model;
}

/*
void thread_server::logUpdated(){}
*/

msg_forwarder::msg_forwarder(int count, int asender, const typeMsg& _msg, thread_server *server_){
    cntfd = count;
    sender = asender;
    msg_ = _msg;
    server = server_;
}

msg_forwarder::~msg_forwarder(){
    wait();
}

void msg_forwarder::run(){
    server->forwardGroupMsg(cntfd, sender, msg_);
}
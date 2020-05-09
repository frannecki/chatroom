#include "client/thread_client.h"

thread_client::thread_client(){
    ;
}

thread_client::~thread_client(){
    printf("[INFO] Main Thread finished.\n");
}

bool thread_client::init(const std::string& addr_srv, 
    const std::string& port_srv, int request_code)
{    
    socket_file = -1;
    
    assert(request_code == CLIENT_LOGIN || request_code == CLIENT_REGISTER);
    is_Running = true;
    is_RecvFile = false;
    cntcont = 0;
    thread_pool.setMaxThreadCount(20);

    if((socket_client = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        emit connection_interrupted();
        return false;
    }
    int port;
    sscanf(port_srv.c_str(), "%d", &port);
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    inet_aton(addr_srv.c_str(), &dest.sin_addr);
    bzero(&(dest.sin_zero), sizeof(dest.sin_zero) / sizeof(dest.sin_zero[0]));
    if(::connect(socket_client, (struct sockaddr*)&dest, sizeof(dest)) < 0){
        return false;
    }
    outputLog("[INFO] Server connected. Socket: " + std::to_string(socket_client));
    if(!sendMsg(request_code, "\0", nickname + " " + password)){
        return false;
    }

    struct usermsg msg_recved;
    bzero(msg_recved.msg, MAXBUFFLEN+1);
    recv(socket_client, (char*)&msg_recved, sizeof(msg_recved), 0);
    if(msg_recved.btype == SERVER_FEEDBACK && 0 == 
        strcmp(msg_recved.msg, "Connection Established."))
    {
        outputLog(std::string("[INFO] Connection to server Established. Socket: ") + std::to_string(socket_client));
        emit connection_established();
    }
    else{
        return false;
    }

    if(request_code == CLIENT_LOGIN){
        if((socket_file = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            emit connection_interrupted();
            return false;;
        }
        if(::connect(socket_file, (struct sockaddr*)&dest, sizeof(dest)) < 0){
            return false;
        }
        outputLog("[INFO] Server file transfer connected. Socket: " + std::to_string(socket_file));
        if(!sendMsg(CLIENT_FILE_SOCKET, "\0", nickname + " " + password, true)){
            return false;
        }
        flushFileSocket();
    }

    workerThread = boost::thread(thread_client::loop, (void*)this);
    tmpFileDir = ".TEMP_" + nickname + "/";
    std::string mkdirTempFolder = "mkdir " + tmpFileDir;
    system(mkdirTempFolder.c_str());
    return true;
}

void thread_client::closeAll(){
    printf("[INFO] Ready to close client.\n");
    {
        boost::unique_lock<boost::shared_mutex> locker(mutexRunning);
        if(!is_Running)  return;  
        is_Running = false;
    }
    {
        boost::unique_lock<boost::mutex> locker(mutexRecvFile);
    }
    sendMsg(CLIENT_LOGOUT, "server", "\0");  // request to logout
    workerThread.join();
    printf("[INFO] Recv thread finished.\n");
    close(socket_client);
}

void thread_client::loop(void* params){
    thread_client* th = (thread_client*)params;
    usermsg msg_recved;
    int bytelen;
    int contact_tab_index;
    while(1){
        bzero(msg_recved.msg, MAXBUFFLEN+1);
        bytelen = recv(th->socket_client, (char*)&msg_recved, sizeof(msg_recved), 0);
        if(bytelen < 0){
            emit th->connection_interrupted();
            break;
        }
        else if(bytelen == 0){
            break;
        }
        th->thread_pool.start(new msgRecver(msg_recved, th));
        {
            boost::shared_lock<boost::shared_mutex>(th->mutexRunning);
            if(!th->is_Running){
                break;
            }
        }
    }
}

void thread_client::recvMsg(const usermsg& msg_){
    if(msg_.btype == SERVER_FEEDBACK){
        if(0 == strcmp("Connection Established.", msg_.msg)){
            //outputLog(std::string("[INFO] Connection to server Established. Socket: ") + std::to_string(socket_client));
            //emit connection_established();
            return;
        }
        else{
            if(0 == strcmp("Registration Succeeded.", msg_.msg)){
                outputLog("[INFO] Registration Succeeded.");
                emit registration_succeeded();
            }
            else if(0 == strcmp("Registration Failed.", msg_.msg)){
                outputLog("[ERROR] Registration Failed!");
            }
            else if(0 == strcmp("Login Failed.", msg_.msg)){
                outputLog("[ERROR] Login Failed!");
                emit login_failed();
            }
            else if(0 == strcmp("Connection Rejected!", msg_.msg)){
                emit connection_rejected();
            }
            bool isNodeRunning;
            {
                boost::shared_lock<boost::shared_mutex> locker(mutexRunning);
                isNodeRunning = is_Running;
            }
            if(isNodeRunning)  closeAll();
        }
    }
    else if(msg_.btype == SERVER_QUERY){
        if(0 != strlen(msg_.msg)){
            printf("[INFO] User(s) found: %s\n", msg_.msg);
            emit users_found(msg_.msg);
        }
    }
    else{
        bool newCont = false;
        if(contacts.count(std::string(msg_.sock_src)) == 0){
            if(-1 == addContact(std::string(msg_.sock_src)))  return;
            else  newCont = true;
        }
        int contact_tab_index = contacts[std::string(msg_.sock_src)];
        if(newCont){
            outputLog("[INFO] Message from new.");
            emit msgFromNew(contact_tab_index);
            newCont = false;
        }

        if(msg_.btype == MESSAGE){
            updateChatBox(contact_tab_index, std::string(msg_.sock_src) + 
                    ": " + std::string(msg_.msg));
        }
        else if(msg_.btype == FILENAME){
            char fname[100];
            int fsize;
            sscanf(msg_.msg, "%d %[^\n]", &fsize, fname);
            updateChatBox(contact_tab_index, 
                    "File from " + std::string(msg_.sock_src) + 
                    ": " + std::string(fname) + " " + std::to_string(fsize >> 10) + " kB");
            //recvFileThread = boost::thread(thread_client::recv_file, this, 
                    //std::string(fname), std::string(msg_.sock_src), fsize);
            boost::thread recvFileThread(thread_client::recv_file, this, 
                    std::string(fname), std::string(msg_.sock_src), fsize);
        }
    }
}

bool thread_client::sendMsg(int btype, const std::string& dest, const std::string& msg, bool use_socket_file){
    if(msg.size() > MAXBUFFLEN){
        printf("[ERROR] Message too long.\n");
        return false;
    }
    usermsg msg_sent;
    msg_sent.btype = btype;
    strcpy(msg_sent.sock_dest, dest.c_str());
    strcpy(msg_sent.msg, msg.c_str());
    int sock = use_socket_file?socket_file:socket_client;
    if(send(sock, (char*)&msg_sent, sizeof(msg_sent), 0) < 0){
        perror("[ERROR] send()");
        emit connection_interrupted();
        return false;
    }
    else{
        //printf("%s Sent message %s\n", msg.c_str(), msg_sent.msg);
        return true;
    }
}

void thread_client::transferFile(const std::string& filename, const std::string& dest){
    //sendFileThread = boost::thread(thread_client::transfer_file, (void*)this, filename, dest);
    boost::thread sendFileThread(thread_client::transfer_file, (void*)this, filename, dest);
}

void thread_client::transfer_file(void* param, std::string filename, std::string dest){
    
    thread_client* th = (thread_client*)param;
    
    //int len = filename.size();
    //int startfname = len;
    //while(startfname > 0 && filename[startfname-1] != '/'){
    //    --startfname;
    //}
    //std::string fname = filename.substr(startfname, len-startfname);
    std::string fname = getFname(filename);
    FILE* fp = fopen(filename.c_str(), "rb");
    fseek(fp, 0L, SEEK_END);
    int fsize = ftell(fp);
    fclose(fp);

    int fd;
    struct stat stat_buf;
    off_t offset = 0;
    if((fd = open(filename.c_str(), O_RDONLY)) < 0){
        printf("[ERROR] Failed to open file %s!\n", filename.c_str());
        return;
    }
    else{
        printf("[INFO] file %s opened\n", filename.c_str());
    }
    fstat(fd, &stat_buf);

    boost::unique_lock<boost::mutex> locker(th->mutexSendFile);
    
    usermsg msg_sent;
    msg_sent.btype = FILENAME;
    strcpy(msg_sent.sock_dest, dest.c_str());
    strcpy(msg_sent.msg, (std::to_string(fsize) + " " + fname).c_str());
    if(send(th->socket_client, (char*)&msg_sent, sizeof(msg_sent), 0) <= 0){
        return;
    }
    
    sendfile(th->socket_file, fd, &offset, stat_buf.st_size);
    close(fd);
    th->flushFileSocket();
    printf("[INFO] file transfer finished: %s.\n", filename.c_str());
}

void thread_client::recv_file(void* param, std::string fname, std::string src, int fsize){
    // fsize is necessary to end receiving process conveniently
    thread_client* th = (thread_client*)param;
    std::string filename =  th->tmpFileDir + fname;
    FILE* fd = fopen(filename.c_str(), "wb");
    char buffer[MAXFILEBUFFLEN];
    int flen = 0, totalflen = 0;
    {
        boost::unique_lock<boost::mutex> locker(th->mutexRecvFile);
        while(true){
            bzero(buffer, MAXFILEBUFFLEN+1);
            if((flen = recv(th->socket_file, buffer, MAXFILEBUFFLEN, 0)) <= 0){
                break;
            }
            fwrite(buffer, 1, flen, fd);
            totalflen += flen;
            if(totalflen >= fsize){
                printf("[FILE] finished: %s.\n", fname.c_str());
                break;
            }
        }
    }
    fclose(fd);
    emit th->file_recv_finished(QString::fromStdString(fname));
}

void thread_client::updateChatBox(int contact, const std::string& cont){
    QStringListModel *chat_box = &(chatbox[contact]);
    chat_box->insertRows(chat_box->rowCount(),1);
    std::stringstream chatbox_msg;
    chatbox_msg << cont.c_str();
    QVariant new_row(QString(chatbox_msg.str().c_str()));
    chat_box->setData(chat_box->index(chat_box->rowCount()-1), new_row);
    emit msgRecvd(contact);
}

void thread_client::outputLog(const std::string& logcont){
    log_model.insertRows(log_model.rowCount(),1);
    std::stringstream log_model_msg;
    log_model_msg << logcont.c_str();
    QVariant new_row(QString(log_model_msg.str().c_str()));
    log_model.setData(log_model.index(log_model.rowCount()-1), new_row);
    emit logUpdated();
}

void thread_client::flushFileSocket(){
    int flag = 1; 
    setsockopt(socket_file, IPPROTO_TCP, TCP_NODELAY, (char*) &flag, sizeof(flag));
    flag = 0;
    setsockopt(socket_file, IPPROTO_TCP, TCP_NODELAY, (char*) &flag, sizeof(flag));
}

QStringListModel* thread_client::chatBox(int tabind){
    return &(chatbox[tabind]);
}

QStringListModel* thread_client::logModel(){
    return &log_model;
}

void thread_client::setNickname(const std::string& nn){
    nickname = nn;
}

void thread_client::setPassword(const std::string& pw){
    password = pw;
}

std::string thread_client::getNickname() const{
    return nickname;
}

int thread_client::addContact(const std::string &srcname){
    if(cntcont >= MAXCONTACTS){
        outputLog(std::string("[ERROR] Maximum contact number excceeded!"));
        return -1;
    }
    else if(contacts.count(srcname) > 0  ||  srcname == nickname){
        outputLog(std::string("[ERROR] Contact in communication!"));
        return -1;
    }
    else{
        contacts.insert(std::pair<std::string, int>(srcname, ++cntcont));
        tab_index[cntcont] = srcname;
        outputLog("[INFO] Added new contact #" + std::to_string(cntcont) + srcname);
        return cntcont;
    }
}

int thread_client::removeContact(int index){
    if(index <= 0 || index > MAXCONTACTS)  return -1;
    else{
        std::string contname = tab_index[index];
        // replace with the last one.
        tab_index[index] = tab_index[cntcont--];
        contacts.erase(contname);
        if(index != cntcont+1){
            contacts[tab_index[index]] = index;
            chatbox[index].setStringList(chatbox[cntcont+1].stringList());
        }
        chatbox[cntcont+1].setStringList(QStringList());
        return cntcont;
    }
}

std::map<std::string, int>* thread_client::getContacts(){
    return &contacts;
}

int thread_client::getCntCont() const{
    return cntcont;
}

std::string thread_client::getContName(int ind){
    return tab_index[ind];
}

msgRecver::msgRecver(const usermsg& _msg, thread_client* client_){
    client = client_;
    msg_ = _msg;
}

msgRecver::~msgRecver(){}

void msgRecver::run(){
    client->recvMsg(msg_);
}

std::string getFname(const std::string& filename){
    std::string fname;
    int idx = 0;
    for(int i = 0; i < filename.size(); ++i){
        if(filename[i] == '/')  idx = i+1;
    }
    fname.assign(filename.begin()+idx, filename.end());
    return fname;
}

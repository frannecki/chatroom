#include "thread_client.h"

thread_client::thread_client(){}

bool thread_client::init(const std::string& addr_srv, const std::string& port_srv){
    
    mutexRunning = new QMutex();
    is_Running = true;
    is_Receiving_File = false;
    cntcont = 0;
    thread_pool.setMaxThreadCount(20);
    
    tmpFileDir = std::string(".TEMP_") + nickname + std::string("/");
    std::string mkdirTempFolder = std::string("mkdir ") + tmpFileDir;
    //system(mkdirTempFolder.c_str());

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
    if(socket_::connect(socket_client, (struct sockaddr*)&dest, sizeof(dest)) < 0){
        return false;
    }
    outputLog(std::string("[INFO] Server connected. Socket: ") + std::to_string(socket_client));
    if(!sendMsg(nickname)){
        outputLog(std::string("[ERROR] send() nickname failed."));
        return false;
    }
    else{
        outputLog(std::string("[INFO] send() nickname succeeded."));
    }
    start();
    return true;
}

thread_client::~thread_client(){
    terminate();
    QThread::wait();
    delete mutexRunning;
}

void thread_client::closeAll(){
    closeClient();
}

void thread_client::closeClient(){
    std::string exitMsg = std::string("server 4 Request out.");
    while(!sendMsg(exitMsg));
    //close(socket_client);
    QMutexLocker locker(mutexRunning);
    is_Running = false;
}

void thread_client::run(){
    char buff[MAXBUFFLEN];
    bzero(buff, MAXBUFFLEN);
    typeMsg msg_;
    int bytelen;
    bool isNodeRunning;
    int contact_tab_index;
    while(true){
        bzero(buff, strlen(buff));
        bytelen = recv(socket_client, buff, MAXBUFFLEN, 0);
        if(bytelen == 0)  continue;
        else if(bytelen < 0){
            emit connection_interrupted();
            break;
        }
        parseRMsg(buff, msg_);
        //recvMsg(bytelen, msg_);
        thread_pool.start(new msgRecver(bytelen, msg_, this));
        {
            QMutexLocker locker(mutexRunning);
            isNodeRunning = is_Running;
        }
        if(!isNodeRunning){
            break;
        }
    }
}

void thread_client::recvMsg(int bytelen, const typeMsg& msg_){
    if(msg_.btype == SERVER_FEEDBACK){
        if(0 == strcmp("Connection Established.", msg_.msg)){
            outputLog(std::string("[INFO] Connection to server Established. Socket: ") + std::to_string(socket_client));
        }
        else{
            QMutexLocker locker(mutexRunning);
            is_Running = false;
            emit connection_rejected();
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
            outputLog(std::string("[INFO] Message from new."));
            emit msgFromNew(contact_tab_index);
            newCont = false;
        }

        if(msg_.btype == MESSAGE){
            updateChatBox(contact_tab_index, std::string(msg_.sock_src) + 
                    std::string(": ") + std::string(msg_.msg));
        }
        else if(msg_.btype == FILENAME){
            if(is_Receiving_File)  return;
            updateChatBox(contact_tab_index, 
                    std::string("File from ") + std::string(msg_.sock_src) + 
                    std::string(": ") + std::string(msg_.msg));
            std::string filename = tmpFileDir + std::string(msg_.msg);
            emit fileRecvd(contact_tab_index, std::string(msg_.msg));
            if((recvfp = fopen(filename.c_str(), "ab")) == NULL){
                outputLog("[ERROR] Opening file failed!");
            }
            else{
                is_Receiving_File = true;
                fname = std::string(msg_.msg);
                fileSrc = std::string(msg_.sock_src);
            }
        }            
        else if(msg_.btype == FILEBUFF){
            if(!is_Receiving_File)  return;
            if(0 != strcmp(msg_.sock_src, fileSrc.c_str()))  return;
            if(bytelen == 0){
                is_Receiving_File = false;
                fclose(recvfp);
            }
            else{
                fwrite(msg_.msg, 1, bytelen, recvfp);
            }
        }
    }
}

bool thread_client::sendMsg(const std::string& mssg){
    if(send(socket_client, mssg.c_str(), mssg.size(), 0) < 0){
        perror("[ERROR] send()");
        printf("[ERROR] Socket: %d.\n", socket_client);
        outputLog("[ERROR] Message not sent due to interrupted connection.");
        emit connection_interrupted();
        return false;
    }
    else  return true;
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

QStringListModel* thread_client::chatBox(int tabind){
    return &(chatbox[tabind]);
}

QStringListModel* thread_client::logModel(){
    return &log_model;
}

void thread_client::setNickname(const std::string& nn){
    nickname = nn;
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
        outputLog(std::string("[INFO] Added new contact #") + std::to_string(cntcont) + srcname);
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

/*
void thread_client::msgRecvd(){}

void thread_client::fileRecvd(){}

void thread_client::connection_rejected(){}

void thread_client::connection_interrupted(){}
*/

msgRecver::msgRecver(int blen, const typeMsg& _msg, thread_client* client_){
    client = client_;
    msg_ = _msg;
    bytelen = blen;
}

msgRecver::~msgRecver(){}

void msgRecver::run(){
    client->recvMsg(bytelen, msg_);
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
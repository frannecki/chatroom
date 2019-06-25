#include "thread_client.h"

thread_client::thread_client(){}

bool thread_client::init(const std::string& addr_srv, const std::string& port_srv){
    
    mutexRunning = new QMutex();
    is_Running = true;
    cntcont = 0;

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
    outputLog(std::string("[INFO] Server connected."));
    if(send(socket_client, nickname.c_str(), nickname.size(), 0) <= 0){
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
    wait();
    delete mutexRunning;
}

void thread_client::closeAll(){
    QMutexLocker locker(mutexRunning);
    is_Running = false;
}

void thread_client::run(){
    char buff[MAXBUFFLEN];
    typeMsg msg_;
    int bytelen;
    bool isNodeRunning;
    int contact_tab_index;
    bool newCont = false;
    while(true){
        bytelen = recv(socket_client, buff, MAXBUFFLEN, 0);
        if(bytelen == 0)  continue;
        if(bytelen < 0){
            close(socket_client);
            emit connection_interrupted();
            break;
        }
        buff[bytelen] = '\0';
        parseRMsg(buff, msg_);

        if(0 == strcmp("server", msg_.sock_src)){
            if(0 == strcmp("Connection Established.", msg_.msg)){
                outputLog(std::string("[INFO] Connection to server Established."));
                continue;
            }
            else{
                emit connection_rejected();
                break;
            }
        }
        
        if(contacts.count(std::string(msg_.sock_src)) == 0){
            if(-1 == addContact(std::string(msg_.sock_src)))  continue;
            else  newCont = true;
        }
        contact_tab_index = contacts[std::string(msg_.sock_src)];
        if(newCont){
            emit msgFromNew(contact_tab_index);
            newCont = false;
        }
        updateChatBox(contact_tab_index, std::string(msg_.sock_src) + 
                        std::string(": ") + std::string(msg_.msg));

        {
            QMutexLocker locker(mutexRunning);
            isNodeRunning = is_Running;
        }
        if(!isNodeRunning){
            break;
        }
    }
    close(socket_client);
}

void thread_client::sendMsg(const std::string& mssg){
    if(send(socket_client, mssg.c_str(), mssg.size(), 0) < 0){
        emit connection_interrupted();
    }
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

#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H
#define MAXCONTACTS 10
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <iostream>
#include <sstream>
#include <string.h>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <map>
#include <string>
#include <assert.h>

#include "utils.h"

class thread_client: public QObject{
    Q_OBJECT
    
public:
    explicit thread_client();
    ~thread_client();
    void closeAll();
    static void loop(void*);
    bool init(const std::string&, const std::string&, int);
    bool sendMsg(const std::string&);
    void recvMsg(int, const typeMsg&);
    QStringListModel* chatBox(int);
    QStringListModel* logModel();
    void setNickname(const std::string&);
    void setPassword(const std::string&);
    std::string getNickname() const;
    std::map<std::string, int>* getContacts();
    void updateChatBox(int, const std::string&);
    int addContact(const std::string&);
    int removeContact(int);
    int getCntCont() const;
    std::string getContName(int);

signals:
    void msgRecvd(int);
    void fileRecvd(int, std::string);
    void logUpdated();
    void msgFromNew(int);
    void connection_established();
    void connection_rejected();
    void connection_interrupted();
    void registration_succeeded();
    void registration_failed();
    void login_failed();
    void file_open_error();
    void users_found(const char*);

private:
    boost::thread workerThread;
    boost::shared_mutex mutexRunning;
    boost::shared_mutex mutexRecvFile;
    QThreadPool thread_pool;
    bool is_Running;
    bool is_Receiving_File;
    int socket_client;
    struct sockaddr_in dest;
    int cntcont;  // number of contacts (<= MAXCONTACTS).
    void outputLog(const std::string&);
    std::string nickname, password;
    std::string fname, fileSrc;
    std::map<std::string, int> contacts;
    QStringListModel log_model;
    QStringListModel chatbox[MAXCONTACTS+1];
    std::string tab_index[MAXCONTACTS+1];
    std::string tmpFileDir;
    FILE* recvfp;
    void closeClient();
};


class msgRecver: public QObject, public QRunnable{
public:
    msgRecver(int, const typeMsg&, thread_client*);
    ~msgRecver();
protected:
    void run();
private:
    thread_client* client;
    typeMsg msg_;
    int bytelen;
};

std::string getFname(const std::string&);

#endif
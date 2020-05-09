#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H
#define MAXCONTACTS 10
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QString>
#include <iostream>
#include <sstream>
#include <string.h>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

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
    bool init(const std::string&, const std::string&, int);
    bool sendMsg(int, const std::string&, const std::string&, bool use_socket_file = false);
    void recvMsg(const usermsg&);
    void transferFile(const std::string&, const std::string&);
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
    static void loop(void*);
    static void transfer_file(void*, std::string, std::string);
    static void recv_file(void*, std::string, std::string, int);

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
    void file_recv_finished(const QString&);
    void users_found(const char*);

private:
    boost::thread workerThread;
    //boost::thread sendFileThread;
    //boost::thread recvFileThread;
    boost::shared_mutex mutexRunning;
    boost::mutex mutexRecvFile;
    boost::mutex mutexSendFile;
    QThreadPool thread_pool;
    bool is_Running, is_RecvFile;
    int socket_client, socket_file;
    struct sockaddr_in dest;
    int cntcont;  // number of contacts (<= MAXCONTACTS).
    void outputLog(const std::string&);
    std::string nickname, password;
    std::string toRecvFilename, toRecvFileSrc;
    std::string fname, fileSrc;
    std::map<std::string, int> contacts;
    QStringListModel log_model;
    QStringListModel chatbox[MAXCONTACTS+1];
    std::string tab_index[MAXCONTACTS+1];
    std::string tmpFileDir;
    FILE* recvfp;

    void flushFileSocket();
};


class msgRecver: public QObject, public QRunnable{
public:
    msgRecver(const usermsg&, thread_client*);
    ~msgRecver();
protected:
    void run();
private:
    thread_client* client;
    usermsg msg_;
};

std::string getFname(const std::string&);

#endif
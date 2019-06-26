#ifndef THREAD_SERVER_H
#define THREAD_SERVER_H
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QThread>
#include <QMutex>
#include <QThreadPool>
#include <QRunnable>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <map>

#include "common_.h"

class thread_server: public QThread{
    Q_OBJECT
public:
    explicit thread_server();
    ~thread_server();
    void closeAll();
    void run();
    QStringListModel* logModel();
    bool init(const std::string& addr_srv, const std::string& port_addr);
    void forwardGroupMsg(int cntfd, int sender, const typeMsg&);

signals:
    void logUpdated();

private:
    bool is_Running;
    QMutex *mutexRunning;
    QThreadPool msg_threadpool;
    struct sockaddr_in addr_server, addr_client;
	int socket_server, socket_client;
	fd_set fs;  // file descriptor set
	int cntfd;  // count of client file descriptors
	userIDs uIDs[MAXUSERNUM];
    QStringListModel log_model;
    std::map<std::string, int> contacts;
    std::map<int, std::string> contacts_ind; 
    void outputLog(const std::string&);
    void loopTask();
    void clrsocket(int);
};


class msg_forwarder: public QObject, public QRunnable{
public:
    msg_forwarder(int, int, const typeMsg&, thread_server*);
    ~msg_forwarder();
protected:
    void run();
private:
    int cntfd, sender;
    typeMsg msg_;
    thread_server *server;
};
#endif
#ifndef THREAD_SERVER_H
#define THREAD_SERVER_H
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QThread>
#include <QMutex>
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
    static void forwardGroupMsg(void*, int sender, const typeMsg&);

signals:
    void logUpdated();

private:
    bool is_Running;
    QMutex *mutexRunning;
    struct sockaddr_in addr_server, addr_client;
	int socket_server, socket_client, epfd;
	int cntfd;  // count of client file descriptors
	userIDs uIDs[MAXUSERNUM];
    QStringListModel log_model;
    std::map<std::string, int> contacts;
    std::map<int, int> contacts_ind; 
    void outputLog(const std::string&);
    void loopTask();
    void clrsocket(int);
};

#endif
#ifndef THREAD_SERVER_H
#define THREAD_SERVER_H
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QObject>
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

#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

#include "utils.h"
#include "mysql_utils.h"

#ifdef MSGCACHE
#include "redis_utils.h"
#endif

//using namespace socket_;
/*
using socket_::socket;
using socket_::connect;
using socket_::bind;
using socket_::accept;
using socket_::send;
using socket_::recv;
*/

class thread_server: public QObject{
    Q_OBJECT

public:
    explicit thread_server();
    ~thread_server();
    void closeAll();
    static void loopTask(void*);
    static void connectStopper(void*);
    QStringListModel* logModel();
    bool init(const std::string& addr_srv, const std::string& port_addr);
    static void forwardGroupMsg(void*, int sender, const typeMsg&);

signals:
    void logUpdated();

private:
    bool is_Running;
    boost::thread workerThread, connThread;
    boost::shared_mutex mutexRunning;
    boost::shared_mutex mutexUIds;
    struct sockaddr_in addr_server, addr_client;
	int socket_server, socket_client, epfd, socket_stopper, socket_stopper_client;
	int cntfd;  // count of client file descriptors
	userIDs uIDs[MAXUSERNUM];
    QStringListModel log_model;
    std::map<std::string, int> contacts;
    std::map<int, int> contacts_ind;
    mysql_spec sql_task;
    void outputLog(const std::string&);
    void clrsocket(int);
#ifdef MSGCACHE
    redis_spec redis_task;
#endif
};

#endif
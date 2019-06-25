#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H
#define MAXCONTACTS 10
#include <QMainWindow>
#include <QStringListModel>
#include <QPixmap>
#include <QThread>
#include <QMutex>
#include <iostream>
#include <sstream>
#include <string.h>
namespace socket_{
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
}
#include <map>
#include <string>

#include "common_.h"
using namespace socket_;

class thread_client: public QThread{
    Q_OBJECT
public:
    explicit thread_client();
    ~thread_client();
    void closeAll();
    void run();
    bool init(const std::string& addr_srv, const std::string& port_addr);
    void sendMsg(const std::string&);
    QStringListModel* chatBox(int);
    QStringListModel* logModel();
    void setNickname(const std::string&);
    std::string getNickname() const;
    std::map<std::string, int>* getContacts();
    void updateChatBox(int, const std::string&);
    int addContact(const std::string&);
    int removeContact(int);
    int getCntCont() const;
    std::string getContName(int);

signals:
    void msgRecvd(int);
    void fileRecvd();
    void logUpdated();
    void msgFromNew(int);
    void connection_rejected();
    void connection_interrupted();

private:
    QMutex *mutexRunning;
    bool is_Running;
    int socket_client;
    struct sockaddr_in dest;
    int cntcont;  // number of contacts (<= MAXCONTACTS).
    void outputLog(const std::string&);
    std::string nickname;
    std::map<std::string, int> contacts;
    QStringListModel log_model;
    QStringListModel chatbox[MAXCONTACTS+1];
    std::string tab_index[MAXCONTACTS+1];
};

#endif
#ifndef UTILS_H
#define UTILS_H
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <string.h>

const int MAXBUFFLEN = 500;
const int MAXFNAMELEN = 100;
const int MAXNAMELEN = 20;
const int MAXUSERNUM = 10;

enum typeStream {
    MESSAGE = 0, 
    FILENAME,
    FILEBUFF, 
    SERVER_FEEDBACK,
    SERVER_QUERY,
    CLIENT_LOGOUT,
    CLIENT_REGISTER,
    CLIENT_LOGIN,
    USER_SEARCH,
    USER_SELECTION,
    SERVER_STOP
};

struct userIDs{
    std::string uname;
    int sockfd;
    epoll_event ev;
    userIDs(): uname(std::string("unknown")), sockfd(0){};
    void reset(){
        uname = std::string("unknown");
        sockfd = 0;
    }
};

struct typeMsg{
    char msg[MAXBUFFLEN];
    int btype;
    char sock_dest[MAXNAMELEN], sock_src[MAXNAMELEN];
};

void parseRMsg(char buff[], typeMsg &msg_);

void parseSMsg(char buff[], typeMsg &msg_);

void composeMsg(char buff[], const std::string& , int, const char*);

void getServerIp();

bool isUsernameOrPasswordValid(const std::string&);

#endif
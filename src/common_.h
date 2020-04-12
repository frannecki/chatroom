#ifndef COMMON_H_
#define COMMON_H_
#define MAXBUFFLEN 500
#define MAXFNAMELEN 100
#define MAXNAMELEN 20
#define MAXUSERNUM 10
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

enum typeStream {
    MESSAGE = 0, 
    FILENAME = 1, 
    FILEBUFF = 2, 
    SERVER_FEEDBACK = 3, 
    CLIENT_LOGOUT = 4
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
#endif
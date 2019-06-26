#ifndef COMMON_H_
#define COMMON_H_
#define MAXBUFFLEN 500
#define MAXFNAMELEN 100
#define MAXNAMELEN 20
#define MAXUSERNUM 10
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string>

enum typeStream {
    MESSAGE = 0, 
    FILENAME = 1, 
    FILEBUFF = 2, 
    SERVER_FEEDBACK = 3, 
    CLIENT_LOGOUT = 4
};

typedef struct name{
    std::string uname;
    int sockfd;
    name(): uname(std::string("unknown")), sockfd(0){};
    void reset(){
        uname = std::string("unknown");
        sockfd = 0;
    }
}userIDs;

typedef struct type{
    char msg[MAXBUFFLEN];
    int btype;
    char sock_dest[MAXNAMELEN], sock_src[MAXNAMELEN];
}typeMsg;

void parseRMsg(char buff[], typeMsg &msg_);

void parseSMsg(char buff[], typeMsg &msg_);
#endif
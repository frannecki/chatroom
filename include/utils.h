#ifndef UTILS_H
#define UTILS_H
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/time.h>
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
const int MAXFILEBUFFLEN = 2048;

enum typeStream {
    MESSAGE = 0, 
    FILENAME,
    FILEEND,
    FILEBUFF, 
    SERVER_FEEDBACK,
    SERVER_QUERY,
    CLIENT_LOGOUT,
    CLIENT_REGISTER,
    CLIENT_LOGIN,
    CLIENT_FILE_SOCKET,
    USER_SEARCH,
    USER_SELECTION,
    SERVER_STOP
};

struct userIDs{
    std::string uname;
    int sockfd_file_dest;
    int sockfd, sockfd_file;
    epoll_event ev;
    epoll_event ev_file;
    userIDs(): uname(std::string("unknown")), sockfd(0){};
    void reset(){
        uname = std::string("unknown");
        sockfd = sockfd_file = -1;
    }
};

struct typeMsg{
    char msg[MAXFILEBUFFLEN];
    int btype;
    char sock_dest[MAXNAMELEN], sock_src[MAXNAMELEN];
};

void parseRMsg(char buff[], typeMsg &msg_);

void parseSMsg(char buff[], typeMsg &msg_);

void composeMsg(char buff[], const std::string& , int, const char*);

void getServerIp();

bool isUsernameOrPasswordValid(const std::string&);

#endif
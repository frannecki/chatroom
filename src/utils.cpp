#include "utils.h"

void composeMsg(usermsg& msg_, const char* sendername, int btype, const char* msg){
    bzero(msg_.msg, MAXBUFFLEN+1);
    msg_.btype = btype;
    strcpy(msg_.sock_src, sendername);
    strcpy(msg_.msg, msg);
}

bool isUsernameOrPasswordValid(const std::string& str){
    if(str.empty())  return false;
    for(auto& ch:str){
        if(ch == ' ')  return false;
    }
    return true;
}
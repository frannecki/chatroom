#include "utils.h"

void composeMsg(usermsg& msg_, const char* sendername, int btype, const char* msg){
    bzero(msg_.msg, MAXBUFFLEN+1);
    msg_.btype = btype;
    strcpy(msg_.sock_src, sendername);
    strcpy(msg_.msg, msg);
}

void composeMsg(char buff[], const char* sendername, int btype, const char* msg){
    buff[0] = '\0';
    strcat(buff, sendername);
    strcat(buff, " ");
    strcat(buff, std::to_string(btype).c_str());
    strcat(buff, " ");
    strcat(buff, msg);
}

void composeMsg(usermsg& msg_, char buff[]){
    sscanf(buff, "%s %d %[^\n]", msg_.sock_src, &(msg_.btype), msg_.msg);
}

bool isUsernameOrPasswordValid(const std::string& str){
    if(str.empty())  return false;
    for(auto& ch:str){
        if(ch == ' ')  return false;
    }
    return true;
}
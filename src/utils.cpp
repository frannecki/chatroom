#include "utils.h"

void parseRMsg(char buff[], typeMsg &msg_){
    msg_.msg[0] = '\0';
    sscanf(buff, "%s %d %[^\n]", msg_.sock_src, &(msg_.btype), msg_.msg);
}

void parseSMsg(char buff[], typeMsg &msg_){
    msg_.msg[0] = '\0';
    sscanf(buff, "%s %d %[^\n]", msg_.sock_dest, &(msg_.btype), msg_.msg);
}

void composeMsg(char buff[], const std::string& sendername, int btype, const char* msg){
    buff[0] = '\0';
    strcat(buff, sendername.c_str());
    strcat(buff, " ");
    strcat(buff, std::to_string(btype).c_str());
    strcat(buff, " ");
    strcat(buff, msg);
}

bool isUsernameOrPasswordValid(const std::string& str){
    if(str.empty())  return false;
    for(auto& ch:str){
        if(ch == ' ')  return false;
    }
    return true;
}

void getServerIp(){
    //TODO;
}
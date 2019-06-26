#include "common_.h"
void parseRMsg(char buff[], typeMsg &msg_){
    msg_.msg[0] = '\0';
    sscanf(buff, "%s %d %[^\n]", msg_.sock_src, &(msg_.btype), msg_.msg);
}

void parseSMsg(char buff[], typeMsg &msg_){
    msg_.msg[0] = '\0';
    sscanf(buff, "%s %d %[^\n]", msg_.sock_dest, &(msg_.btype), msg_.msg);
}
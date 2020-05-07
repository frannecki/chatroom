#ifdef MSGCACHE
#include "server/redis_utils.h"

redis_spec::~redis_spec(){
    freeReplyObject(reply);
    conn = NULL;
    reply = NULL;
}

unsigned int redis_spec::init(const char* host, unsigned int port){
    conn = NULL;
    reply = NULL;
    conn = redisConnect(host, port);
    if(!conn || conn->err){
        return REDIS_CONNECTION_FAILED;
    }
    return REDIS_CONNECTION_ESTABLISHED;
}

int redis_spec::getNumMsg(const char* username){
    strcpy(current_username, username);
    reply = (redisReply*)redisCommand(conn, "LLEN %s", username);
    return reply->integer;
}

void redis_spec::cacheMsg(const char* dest, const char* buf){
    printf("[INFO] Caching message sent to %s: %s\n", dest, buf);
    redisCommand(conn, "RPUSH %s %s", dest, buf);
}

const char* redis_spec::retrieveMsg(){
    reply = (redisReply*)redisCommand(conn, "LPOP %s", current_username);
    return reply->str;
}
#endif
#ifndef REDIS_UTILS_H
#define REDIS_UTILS_H
#include "utils.h"
#include <hiredis/hiredis.h>

enum redisStatus{
    REDIS_CONNECTION_ESTABLISHED = 0,
    REDIS_CONNECTION_FAILED,
};

class redis_spec{
public:
    ~redis_spec();
    unsigned int init(const char*, unsigned int);
    void cacheMsg(const char*, const char*);
    const char* retrieveMsg();
    int getNumMsg(const char*);

private:
    redisContext* conn;
    redisReply* reply;
    char buff[200];
    char current_username[15];
};

#endif
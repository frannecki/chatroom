#ifndef MYSQL_UTILS_H
#define MYSQL_UTILS_H
#include <mysql/mysql.h>
#include <string.h>
#include "utils.h"

enum dbStatus{
    CONNECTION_ESTABLISHED = 0,
    CONNECTION_FAILED,
    USER_INVALID,
    USER_VALID,
    LOGIN_VALID,
    REGISTERED,
    QUERY_SUCCEEDED,
    PASSWD_INCORRECT,
    QUERY_FAILED,
    USERNAME_OCCUPIED
};

class mysql_spec{
public:
    mysql_spec();
    ~mysql_spec();
    MYSQL_RES* getResult() const;
    unsigned int loginUser(const char*, const char*);
    unsigned int insertUser(const char*, const char*);
    unsigned int queryUser(const char*, bool like = true);
    unsigned int init(const char*, const char*, const char*, 
        const char*, unsigned int port = 3306, const char *unix_socket = NULL, 
        unsigned long client_flag = CLIENT_FOUND_ROWS, const char* table = "chatroom_user_data");

private:
    const char* table;
    MYSQL* conn;
    MYSQL_RES* result;
    MYSQL_ROW row;
    unsigned int queryTable(const char*);
};


#endif
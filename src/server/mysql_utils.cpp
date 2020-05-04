#include "server/mysql_utils.h"

mysql_spec::mysql_spec(){
    conn = NULL;
    result = NULL;
}

mysql_spec::~mysql_spec(){
    if(conn){
        mysql_close(conn);
    }
}

unsigned int mysql_spec::init(const char* host, const char* user, const char* passwd, 
        const char* db, unsigned int port, const char *unix_socket, 
        unsigned long client_flag, const char* table)
{
    this->table = table;
    conn = mysql_init(conn);
    if(!mysql_real_connect(conn, host, user, passwd, db, port, unix_socket, client_flag)){
        return CONNECTION_FAILED;
    }
    else  return CONNECTION_ESTABLISHED;
}

unsigned int mysql_spec::loginUser(const char* username, const char* password){
    char query[100] = "select * from ";
    strcat(query, table);
    strcat(query, " where username = '");
    strcat(query, username);
    strcat(query, "'");
    if(QUERY_SUCCEEDED != queryTable(query)){
        return QUERY_FAILED;
    }
    else if(mysql_num_rows(result) == 0){
        return USER_INVALID;
    }
    else{
        row = mysql_fetch_row(result);
        if(0 != strcmp(row[2], password)){
            return PASSWD_INCORRECT;
        }
        else return LOGIN_VALID;
    }
}

unsigned int mysql_spec::insertUser(const char* username, const char* password){
    if(loginUser(username, password) != USER_INVALID){
        return USERNAME_OCCUPIED;
    }
    char query[100] = "insert into ";
    strcat(query, table);
    strcat(query, " (username, password) ");
    strcat(query, "values('");
    strcat(query, username);
    strcat(query, "','");
    strcat(query, password);
    strcat(query, "')");
    if(QUERY_SUCCEEDED != queryTable(query)){
        return QUERY_FAILED;
    }
    else return REGISTERED;
}

unsigned int mysql_spec::queryUser(const char* username, bool like){
    char query[100] = "select * from ";
    strcat(query, table);
    strcat(query, " where username like '");
    strcat(query, username);
    if(like)  strcat(query, "%");  
    strcat(query, "'");
    // search for users whose names are like that in the parameter list
    if(QUERY_SUCCEEDED != queryTable(query)){
        return QUERY_FAILED;
    }
    else if(mysql_num_rows(result) == 0){
        return USER_INVALID;
    }
    else{
        return USER_VALID;
    }
}

unsigned int mysql_spec::queryTable(const char* cmd){
    if(mysql_query(conn, cmd)){
        return QUERY_FAILED;
    }
    result = mysql_store_result(conn);
    return QUERY_SUCCEEDED;
}

MYSQL_RES* mysql_spec::getResult() const{
    return result;
}

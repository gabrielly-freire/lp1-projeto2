#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <mysql/mysql.h>

class Connection {
    private:
        MYSQL* conn;
    public:
        Connection();
        ~Connection();
        MYSQL* getConnection();
};

#endif
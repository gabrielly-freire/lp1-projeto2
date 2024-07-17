#include "../../include/connection/Connection.hpp"
#include <iostream>

Connection::Connection() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "Erro ao inicializar a conexão: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_real_connect(conn, "localhost", "root", "Password123#@!", "controlador_viagens_db", 0, NULL, 0) == NULL) {
        std::cerr << "Erro ao conectar ao banco de dados: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return;
    }

}

Connection::~Connection() {
    mysql_close(conn);
}

MYSQL* Connection::getConnection() {
    return this->conn;
}

#include "../../include/connection/Connection.hpp"
#include <iostream>

Connection::Connection() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "Erro ao inicializar a conexão: " << mysql_error(conn) << std::endl;
        return;
    }

    // Atribuições das variáveis de conexão com o banco
    const char* host = "localhost";
    const char* user = "root";
    const char* password = "nova_senha";
    const char* database = "controlador_viagens_db"; // nome do banco do scritp
    unsigned int port = 0;  // Porta padrão para MySQL
    const char* unix_socket = NULL;  // Usar socket padrão
    unsigned long client_flag = 0;   // Flags padrão para cliente

    if (mysql_real_connect(conn, host, user, password, database, port, unix_socket, client_flag) == NULL) {
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
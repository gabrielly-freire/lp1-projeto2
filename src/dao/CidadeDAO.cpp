#include "../../include/dao/CidadeDAO.hpp"
#include "../../include/model/Cidade.hpp"
#include <iostream>

CidadeDAO::CidadeDAO(Connection& conn): connection(conn){}

void CidadeDAO::create(Cidade cidade){
    char query[200]; 
    sprintf(query, "INSERT INTO cidades (nome) VALUES ('%s');", cidade.getNome().c_str());
    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

std::vector<Cidade*> CidadeDAO::findAll(){
    std::vector<Cidade*> cidades;
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[] = "SELECT * FROM cidades;"; 
    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return cidades;
    }
    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string nome = row[1];
        Cidade* cidade = new Cidade(id, nome);
        cidades.push_back(cidade);
    }
    mysql_free_result(result);

    return cidades;
}

Cidade* CidadeDAO::findById(int id) {
    Cidade* cidade = new Cidade("");
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];
    sprintf(query, "SELECT * FROM cidades WHERE id = %d;", id);

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return cidade;
    }

    result = mysql_store_result(connection.getConnection());
    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return cidade;
    }

    row = mysql_fetch_row(result);
    if (row) {
        int id1 = std::stoi(row[0]);
        std::string nome = row[1];
        Cidade* cidade=new Cidade (id, nome);
        mysql_free_result(result);
        return cidade;
    }

    mysql_free_result(result);
    return cidade;  
}

Cidade* CidadeDAO::findByNome(std::string nome) {
    Cidade* cidade = new Cidade("");
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];

    sprintf(query, "SELECT * FROM cidades WHERE nome = '%s';", nome.c_str());

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return cidade;
    }

    result = mysql_store_result(connection.getConnection());
    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return cidade;
    }

    row = mysql_fetch_row(result);
    if (row) {
        int id = std::stoi(row[0]); 
        std::string nomeCidade = row[1];
        Cidade* cidade = new Cidade(id, nomeCidade);
    }

    mysql_free_result(result);
    return cidade;  
}

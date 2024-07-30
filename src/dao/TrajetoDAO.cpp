#include "../../include/dao/TrajetoDAO.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include <iostream>
#include <vector>
#include <mysql/mysql.h>

TrajetoDAO::TrajetoDAO(Connection& conn): connection(conn) {}

void TrajetoDAO::create(Trajeto trajeto){
    CidadeDAO cidadeDAO(connection);
    
    char query[200]; 
    sprintf(query, "INSERT INTO trajetos (id_cidade_origem, id_cidade_destino, id_tipo_trajeto, distancia) VALUES (%d, %d, %d, %d);", 
            trajeto.getOrigem()->getId(), trajeto.getDestino()->getId(), trajeto.getTipo(), trajeto.getDistancia());
    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

std::vector<Trajeto*> TrajetoDAO::findAll(){
    std::vector<Trajeto*> trajetos;
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[] = "SELECT * FROM trajetos;";
    
    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return trajetos;
    }
    
    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        int idOrigem = std::stoi(row[1]);
        int idDestino = std::stoi(row[2]);
        int tipo = std::stoi(row[3]);
        int distancia = std::stoi(row[4]);
        
        CidadeDAO dao(connection);
        Cidade* origem = dao.findById(idOrigem);
        Cidade* destino = dao.findById(idDestino);
        
        Trajeto* trajeto = new Trajeto(id, origem, destino, tipo, distancia);
        trajetos.push_back(trajeto);
    }
    mysql_free_result(result);

    return trajetos;
}

Trajeto* TrajetoDAO::findById(int id){
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];
    sprintf(query, "SELECT * FROM trajetos WHERE id = %d;", id);
    
    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }
    
    result = mysql_store_result(connection.getConnection());
    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    row = mysql_fetch_row(result);
    if(row){
        int idOrigem = std::stoi(row[1]);
        int idDestino = std::stoi(row[2]);
        int tipo = std::stoi(row[3]);
        int distancia = std::stoi(row[4]);
        
        CidadeDAO dao(connection);
        Cidade* origem = dao.findById(idOrigem);
        Cidade* destino = dao.findById(idDestino);
        
        Trajeto* trajeto = new Trajeto(id, origem, destino, tipo, distancia);
        return trajeto;
    }

    mysql_free_result(result);
    return nullptr;
}

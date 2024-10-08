#include "../../include/dao/TransporteDAO.hpp"
#include "../../include/model/Transporte.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include <mysql/mysql.h>
#include <vector>
#include <iostream>

TransporteDAO::TransporteDAO(Connection& conn): connection(conn) {}

void TransporteDAO::create(Transporte transporte) {
    CidadeDAO cidadeDAO(connection);
    char query[1024];
    sprintf(query, 
        "INSERT INTO transportes (nome, tipo, capacidade_passageiros, velocidade, distancia_entre_descanso, tempo_de_descanso,tempo_de_descanso_atual, id_cidade_atual) "
        "VALUES ('%s', %d, %d, %d, %d, %d, %d, %d);",
        transporte.getNome().c_str(), 
        transporte.getTipo(),
        transporte.getCapacidade(), 
        transporte.getVelocidade(), 
        transporte.getDistanciaEntreDescansos(), 
        transporte.getTempoDescanso(),
        transporte.getTempoDescansoAtual(), 
        transporte.getLocalAtual()->getId());

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

Transporte* TransporteDAO::findById(int id) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];
    sprintf(query, "SELECT * FROM transportes WHERE id = %d;", id);

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    result = mysql_store_result(connection.getConnection());
    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    row = mysql_fetch_row(result);
    if (row) {
        int id = std::stoi(row[0]);
        std::string nome = row[1];
        int tipo = std::stoi(row[2]);
        int capacidade = std::stoi(row[3]);
        int velocidade = std::stoi(row[4]);
        int distancia_entre_descansos = std::stoi(row[5]);
        int tempo_de_descanso = std::stoi(row[6]);
        int tempo_de_descanso_atual = std::stoi(row[7]);
        int idLocal = std::stoi(row[8]);
        CidadeDAO dao(connection);

        Cidade* localAtual = dao.findById(idLocal);
        Transporte* transporte = new Transporte(id, nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso,tempo_de_descanso_atual, localAtual);
        mysql_free_result(result);
        return transporte;
    }

    mysql_free_result(result);
    return nullptr;
}

Transporte* TransporteDAO::findByNome(std::string nome) {
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];

    sprintf(query, "SELECT * FROM transportes WHERE nome = '%s';", nome.c_str());

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    result = mysql_store_result(connection.getConnection());
    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    row = mysql_fetch_row(result);
    if (row) {
        int id = std::stoi(row[0]);
        std::string nome = row[1];
        int tipo = std::stoi(row[2]);
        int capacidade = std::stoi(row[3]);
        int velocidade = std::stoi(row[4]);
        int distancia_entre_descansos = std::stoi(row[5]);
        int tempo_de_descanso = std::stoi(row[6]);
        int tempo_de_descanso_atual = std::stoi(row[7]);
        int idLocal = std::stoi(row[8]);
        CidadeDAO dao(connection);

        Cidade* localAtual = dao.findById(idLocal);
        Transporte* transporte = new Transporte(id, nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, tempo_de_descanso_atual,localAtual);
        mysql_free_result(result);
        return transporte;
    }


    mysql_free_result(result);
    return nullptr;
}

std::vector<Transporte*> TransporteDAO::findAll(){
    std::vector<Transporte*> transportes;
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[] = "SELECT * FROM transportes;";

    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return transportes;
    }

    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string nome = row[1];
        int tipo = std::stoi(row[2]);
        int capacidade = std::stoi(row[3]);
        int velocidade = std::stoi(row[4]);
        int distancia_entre_descansos = std::stoi(row[5]);
        int tempo_de_descanso = std::stoi(row[6]);
        int tempo_de_descanso_atual = std::stoi(row[7]);
        int idLocal = std::stoi(row[8]);
        CidadeDAO dao(connection);

        Cidade* localAtual = dao.findById(idLocal);
        Transporte* transporte = new Transporte(id, nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso,tempo_de_descanso_atual, localAtual);
        transportes.push_back(transporte);
    }
    mysql_free_result(result);

    return transportes;
}

void TransporteDAO::setIdCidadeAtual(int id_transporte, int id_nova_cidade){
    char query[200];

    sprintf(query, "UPDATE transportes SET id_cidade_atual = %d WHERE id = %d;", id_nova_cidade, id_transporte);

    if (mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}
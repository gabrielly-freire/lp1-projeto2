#include "../../include/dao/ViagemDAO.hpp"
#include "../../include/model/Viagem.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include "../../include/dao/TransporteDAO.hpp"
#include "../../include/dao/PassageiroDAO.hpp"
#include <mysql/mysql.h>
#include <vector>
#include <iostream>


ViagemDAO::ViagemDAO(Connection& conn): connection(conn) {}
void ViagemDAO::create(Viagem viagem){
    MYSQL *mysql = connection.getConnection();
    char query[200];
    sprintf(query,
    "INSERT INTO viagens (id, id_transporte, id_cidade_origem, id_cidade_destino, horas_em_transito, em_andamento) " 
    "VALUES (%d, %d, %d, %d, %d, %d);", 
    viagem.getId(),
    viagem.getTransporte()->getId(),
    viagem.getOrigem()->getId(),
    viagem.getDestino()->getId(),
    viagem.getHoraEmTransito(),
    viagem.isEmAndamento() ? 1 : 0);

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }

    std::vector<Passageiro*> passageiros = viagem.getPassageiros();
    for (Passageiro* passageiro : passageiros) {
        char query_passageiro[100];
        sprintf(query_passageiro,
                "INSERT INTO passageiros_Viagem (id_viagem, id_passageiro) VALUES (%d, '%s');",
                viagem.getId(),
                passageiro->getCpf().c_str());

        if (mysql_query(mysql, query_passageiro) != 0) {
            std::cerr << "Erro ao executar a query: " << mysql_error(mysql) << std::endl;
            return;
        }
    }
}

std::vector<Passageiro*> ViagemDAO::getPassageiros(int id_viagem) {
    MYSQL *mysql = connection.getConnection();
    std::vector<Passageiro*> passageiros;
    char query[256];

    sprintf(query,
        "SELECT id_passageiro FROM passageiros_Viagem WHERE id_viagem = %d;",
        id_viagem);


    if (mysql_query(mysql, query) != 0) {
        std::cerr << "Erro ao executar a query: " << mysql_error(mysql) << std::endl;
        return passageiros;
    }

    MYSQL_RES *result = mysql_store_result(mysql);

    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(mysql) << std::endl;
        return passageiros;
    }

    PassageiroDAO passageiroDAO(connection); 

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::string cpf = row[0];
        Passageiro* passageiro = passageiroDAO.findByCpf(cpf);
        if (passageiro != nullptr) {
            passageiros.push_back(passageiro);
        }
    }

    mysql_free_result(result);
    return passageiros;
}

Viagem* ViagemDAO::findById(int id){
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
        int id_transporte = std::stoi(row[1]);
        int id_cidade_origem = std::stoi(row[1]);
        int id_cidade_destino  = std::stoi(row[2]);
        int horas_em_transito = std::stoi(row[3]);
        bool em_andamento = std::stoi(row[4]) ? 1 : 0;
        
        TransporteDAO dao(connection);
        CidadeDAO daoo(connection);
        PassageiroDAO daooo(connection);
        Transporte* transporte = dao.findById(id_transporte);
        Cidade* cidade_origem = daoo.findById(id_cidade_origem);
        Cidade* cidade_destino = daoo.findById(id_cidade_destino);
        std::vector<Passageiro*> passageiros = getPassageiros(id);

        Viagem* viagem = new Viagem(id, transporte, passageiros, cidade_origem, cidade_destino, horas_em_transito, em_andamento);
        mysql_free_result(result);
        return viagem;
    }

    mysql_free_result(result);
    return nullptr;
}
#include "../../include/dao/ViagemDAO.hpp"
#include "../../include/model/Viagem.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include "../../include/dao/TransporteDAO.hpp"
#include "../../include/dao/PassageiroDAO.hpp"
#include "../../include/dao/TrajetoDAO.hpp"
#include <mysql/mysql.h>
#include <vector>
#include <iostream>

//Inserir viagem no banco de dados sem o trajeto direto ou melhor trajeto.
ViagemDAO::ViagemDAO(Connection& conn): connection(conn) {}

void ViagemDAO::create(Viagem viagem){
    MYSQL *mysql = connection.getConnection();
    char query[200];
    
    //Inserir viagem ao banco de dados na tabela "viagebs"
    sprintf(query,
    "INSERT INTO viagens (id_transporte, id_cidade_origem, id_cidade_destino, horas_em_transito, status_viagem) " 
    "VALUES (%d, %d, %d, %d, %d);", 
    viagem.getTransporte()->getId(),
    viagem.getOrigem()->getId(),
    viagem.getDestino()->getId(),
    viagem.getHoraEmTransito(),
    viagem.getStatusViagem());

    if (mysql_query(connection.getConnection(), query)) {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }

    //Adicionar passageiros à ultima viagem cadastrada no banco de dados na tabela "passageiros_viagem"
    ViagemDAO dao(connection);
    std::vector<Passageiro*> passageiros = viagem.getPassageiros();
    Viagem* nova_viagem = dao.findUltimaViagem();
    for (Passageiro* passageiro : passageiros) {
        char query_passageiro[100];
        sprintf(query_passageiro,
                "INSERT INTO passageiros_viagem (id_viagem, id_passageiro) VALUES (%d, '%s');",
                nova_viagem->getId(),
                passageiro->getCpf().c_str());

        if (mysql_query(mysql, query_passageiro) != 0) {
            std::cerr << "Erro ao executar a query: " << mysql_error(mysql) << std::endl;
            return;
        }
    }

    //Adicionar o trajeto de viagem ao banco de dados na tabela "trajetos_viagem"
    std::vector<Trajeto*> trajetos = viagem.getTrajetos();
    for (Trajeto* trajeto : trajetos) {
        char query_trajeto[100];
        sprintf(query_trajeto,
                "INSERT INTO trajetos_viagem (id_viagem, id_trajeto) VALUES (%d, %d);",
                nova_viagem->getId(),
                trajeto->getId());

        if (mysql_query(mysql, query_trajeto) != 0) {
            std::cerr << "Erro ao executar a query: " << mysql_error(mysql) << std::endl;
            return;
        }
    }
}

//Retornar os passageiros de uma determinada viagem
std::vector<Passageiro*> ViagemDAO::getPassageiros(int id_viagem) {
    MYSQL *mysql = connection.getConnection();
    std::vector<Passageiro*> passageiros;
    char query[256];

    sprintf(query,
        "SELECT id_passageiro FROM passageiros_viagem WHERE id_viagem = %d;",
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

//Retornar os trajetos de uma determinada viagem
std::vector<Trajeto*> ViagemDAO::getTrajetos(int id_viagem) {
    MYSQL *mysql = connection.getConnection();
    std::vector<Trajeto*> trajetos;
    char query[256];

    sprintf(query,
        "SELECT id_trajeto FROM trajetos_viagem WHERE id_viagem = %d;",
        id_viagem);


    if (mysql_query(mysql, query) != 0) {
        std::cerr << "Erro ao executar a query: " << mysql_error(mysql) << std::endl;
        return trajetos;
    }

    MYSQL_RES *result = mysql_store_result(mysql);

    if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(mysql) << std::endl;
        return trajetos;
    }

    TrajetoDAO trajetoDAO(connection); 

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id_trajeto = std::stoi(row[0]);
        Trajeto* trajeto = trajetoDAO.findById(id_trajeto);
        if (trajeto != nullptr) {
            trajetos.push_back(trajeto);
        }
    }

    mysql_free_result(result);
    return trajetos;
}


Viagem* ViagemDAO::findById(int id){
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];
    sprintf(query, "SELECT * FROM viagens WHERE id = %d;", id);

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
        int id_cidade_origem = std::stoi(row[2]);
        int id_cidade_destino  = std::stoi(row[3]);
        int horas_em_transito = std::stoi(row[4]);
        int status = std::stoi(row[5]);
        
        TransporteDAO dao(connection);
        CidadeDAO daoo(connection);
        PassageiroDAO daooo(connection);
        TrajetoDAO trajetoDAO(connection);
        Transporte* transporte = dao.findById(id_transporte);
        Cidade* cidade_origem = daoo.findById(id_cidade_origem);
        Cidade* cidade_destino = daoo.findById(id_cidade_destino);
        std::vector<Passageiro*> passageiros = getPassageiros(id);
        std::vector<Trajeto*> trajetos = getTrajetos(id);
        
        Viagem* viagem = new Viagem(id, transporte, passageiros, trajetos, cidade_origem, cidade_destino, horas_em_transito, status);
        mysql_free_result(result);
        return viagem;
    }

    mysql_free_result(result);
    return nullptr;
}

std::vector<Viagem*> ViagemDAO::findAll(){
    std::vector<Viagem*> viagens;
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[] = "SELECT * FROM viagens;";

    if(mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return viagens;
    }

    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        int id_transporte = std::stoi(row[1]);
        int id_cidade_origem = std::stoi(row[2]);
        int id_cidade_destino  = std::stoi(row[3]);
        int horas_em_transito = std::stoi(row[4]);
        int status = std::stoi(row[5]);
        
        TransporteDAO dao(connection);
        CidadeDAO daoo(connection);
        PassageiroDAO daooo(connection);
        TrajetoDAO trajetoDao(connection);
        Transporte* transporte = dao.findById(id_transporte);
        Cidade* cidade_origem = daoo.findById(id_cidade_origem);
        Cidade* cidade_destino = daoo.findById(id_cidade_destino);
        std::vector<Passageiro*> passageiros = getPassageiros(id);
        std::vector<Trajeto*> trajetos= getTrajetos(id);
        
        Viagem* viagem = new Viagem(id, transporte, passageiros, trajetos, cidade_origem, cidade_destino, horas_em_transito, status);
        viagens.push_back(viagem);
    }
    mysql_free_result(result);

    return viagens;
}

Viagem* ViagemDAO::findUltimaViagem() {
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];
    
    sprintf(query, "SELECT * FROM viagens ORDER BY id DESC LIMIT 1;");
    
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
        int id_cidade_origem = std::stoi(row[2]);
        int id_cidade_destino = std::stoi(row[3]);
        int horas_em_transito = std::stoi(row[4]);
        int status = std::stoi(row[5]);
        
        TransporteDAO transporteDao(connection);
        CidadeDAO cidadeDao(connection);
        PassageiroDAO passageiroDao(connection);
        TrajetoDAO trajetoDAO(connection);
        
        Transporte* transporte = transporteDao.findById(id_transporte);
        Cidade* cidade_origem = cidadeDao.findById(id_cidade_origem);
        Cidade* cidade_destino = cidadeDao.findById(id_cidade_destino);
        std::vector<Passageiro*> passageiros = getPassageiros(id);
        std::vector<Trajeto*> trajetos = getTrajetos(id);
 
        Viagem* viagem = new Viagem(id, transporte, passageiros, trajetos, cidade_origem, cidade_destino, horas_em_transito, status);
        
        mysql_free_result(result);
        
        return viagem;
    }
    
    mysql_free_result(result);
    return nullptr;
}

void ViagemDAO::update(Viagem& viagem) {
    std::cerr << "Status da viagem: " << viagem.getStatusViagem() << std::endl;

    if (viagem.getStatusViagem() == 2) {

        std::string query = "UPDATE viagens SET horas_em_transito = horas_em_transito + 1"
                            " WHERE id = " + std::to_string(viagem.getId()) +
                            " AND status_viagem = 2";

        if (mysql_query(connection.getConnection(), query.c_str())) {
            std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        }

        if (viagem.getHoraEmTransito() >= viagem.getTempoTotalViagem()) {

            query = "UPDATE viagens SET status_viagem = 3 WHERE id = " + std::to_string(viagem.getId());
            

            if (mysql_query(connection.getConnection(), query.c_str())) {
                std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
            } else {
                std::cerr << "A viagem " << viagem.getId() << " chegou a seu destino." << std::endl;
            }
        }
    } else {
        std::cerr << "A viagem não está em andamento. Nenhuma atualização foi realizada." << std::endl;
    }
}

void ViagemDAO::setHorasEmTransito(int id_viagem, int horas_em_transito){
    char query[200];

    sprintf(query, "UPDATE viagens SET horas_em_transito = %d WHERE id = %d;", horas_em_transito, id_viagem);

    if (mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

void ViagemDAO::setStatusViagem(int id_viagem, int status_viagem){
    char query[200];

    sprintf(query, "UPDATE viagens SET status_viagem = %d WHERE id = %d;", status_viagem, id_viagem);

    if (mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

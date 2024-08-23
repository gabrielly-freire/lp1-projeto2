#include "../../include/dao/PassageiroDAO.hpp"
#include "../../include/model/Passageiro.hpp"
#include <iostream>

//Contrutor
PassageiroDAO::PassageiroDAO(Connection& conn): connection(conn){}

//Destrutor
PassageiroDAO::~PassageiroDAO(){
}

void PassageiroDAO::createPassageiro(Passageiro passageiro){

    char query[200];
    sprintf(query, "INSERT INTO passageiros (cpf, nome, id_cidade_atual) VALUES ('%s', '%s', '%d');", passageiro.getCpf().c_str(), passageiro.getNome().c_str(), passageiro.getLocalAtual()->getId());
    
    if (mysql_query(connection.getConnection(), query))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}

vector<Passageiro *> PassageiroDAO::findAll()
{
    vector<Passageiro *> passageiros;
    MYSQL_RES *result;
    MYSQL_ROW row;

    char query[] = "SELECT * FROM passageiros";
    if (mysql_query(connection.getConnection(), query))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return passageiros;
    }

    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result)))
    {
        string cpf = row[0];
        string nome = row[1];
        int idCidade = stoi(row[2]);

        CidadeDAO cidade(connection);
        Cidade *cidadeAtual = cidade.findById(idCidade);
        Passageiro *passageiro = new Passageiro(nome, cpf, cidadeAtual);
        passageiros.push_back(passageiro);
    }

    mysql_free_result(result);
    return passageiros;
}

Passageiro* PassageiroDAO::findByCpf(string cpf){
    MYSQL_RES* result;
    MYSQL_ROW row;
    char query[200];

    sprintf(query, "SELECT * FROM passageiros WHERE cpf = '%s';", cpf.c_str());

    if (mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    result = mysql_store_result(connection.getConnection());

     if (result == NULL) {
        std::cerr << "Erro ao armazenar o resultado: " << mysql_error(connection.getConnection()) << std::endl;
        return nullptr;
    }

    row = mysql_fetch_row(result);

    if (row)
    {
        string nome = row[1];
        int idCidadeAtual = stoi(row[2]);
        CidadeDAO cidade(connection);
        Cidade* cidadeAtual = cidade.findById(idCidadeAtual);
        Passageiro* passageiro = new Passageiro(nome, cpf, cidadeAtual);
        mysql_free_result(result);
        return passageiro;
    }

    return nullptr;
}
void PassageiroDAO::setIdCidadeAtual(string cpf, int id_nova_cidade){
    char query[200];

    sprintf(query, "UPDATE passageiros SET id_cidade_atual = %d WHERE cpf = '%s';", id_nova_cidade, cpf.c_str());

    if (mysql_query(connection.getConnection(), query)){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}
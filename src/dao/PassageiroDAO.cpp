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
    sprintf(query, "INSERT INTO trajetos (cpf, nome, id_cidade_atual) VALUES ('%s', '%s', '%d');", passageiro.getCpf().c_str(), passageiro.getNome().c_str(), passageiro.getLocalAtual()->getId());
    
    if (mysql_query(connection.getConnection(), query))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return;
    }
}
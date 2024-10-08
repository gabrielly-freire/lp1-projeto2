#ifndef CIDADEDAO_HPP
#define CIDADEDAO_HPP

#include "../connection/Connection.hpp"
#include "mysql/mysql.h"
#include <vector>
#include "../model/Cidade.hpp"

//Modificação teste
class CidadeDAO{
    private:
        Connection& connection;
    public:
        CidadeDAO(Connection& connection);
        void create(Cidade cidade);
        std::vector<Cidade*> findAll();
        Cidade* findById(int id);
        Cidade* findByNome(std::string nome);
        void setVisitas(int id_cidade, int quantidade_de_visitas);
};

#endif
#ifndef TRANSPORTEDAO_HPP
#define TRANSPORTEDAO_HPP

#include "../connection/Connection.hpp"
#include "mysql/mysql.h"
#include <vector>
#include "../model/Transporte.hpp"
#include "./CidadeDAO.hpp"


class TransporteDAO{
    private:
        Connection& connection;
    public:
        TransporteDAO(Connection& connection);
        void create(Transporte transporte);
        Transporte* findById(int id);
        Transporte* findByNome(std::string nome);
        std::vector<Transporte*> findAll();
};
#endif
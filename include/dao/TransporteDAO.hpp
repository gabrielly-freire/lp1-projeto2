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

        TransporteDAO(Connection &conn);
        void create(Transporte* transporte);
        std::vector<Transporte*> findAll();
        Transporte* findById(int id);
        Transporte* findByNome(std::string nome);

};
#endif
#ifndef TRAJETODAO_HPP
#define TRAJETODAO_HPP

#include <mysql/mysql.h>
#include "../connection/Connection.hpp"
#include <vector>
#include "../model/Trajeto.hpp"

class TrajetoDAO{
    private:
        Connection& connection;
    public:
        TrajetoDAO(Connection& connection);
        void create(Trajeto trajeto);
        std::vector<Trajeto*> findAll();
        Trajeto* findById(int id);
};

#endif
#ifndef PASSAGEIRODAO_HPP
#define CPASSAGEIRODAO_HPP

#include "../connection/Connection.hpp"
#include "mysql/mysql.h"
#include <vector>
#include "../model/Passageiro.hpp"

using namespace std;

class PassageiroDAO{

private:
    Connection& connection;
public:
    PassageiroDAO(Connection& connection);
    ~PassageiroDAO();
    void createPassageiro(Passageiro passageiro);
    vector<Passageiro*> findAll();
    Passageiro* findById(int id);
    Passageiro* findByNome(string nome);
    Passageiro* findByCidadeAtual(int idCidadeAtual);
};



#endif
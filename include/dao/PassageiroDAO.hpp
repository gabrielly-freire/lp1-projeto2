#ifndef PASSAGEIRODAO_HPP
#define CPASSAGEIRODAO_HPP

#include "../connection/Connection.hpp"
#include "mysql/mysql.h"
#include <vector>
#include "../model/Passageiro.hpp"
#include "CidadeDAO.hpp"

using namespace std;

class PassageiroDAO{

private:
    Connection& connection;
public:
    PassageiroDAO(Connection& connection);
    ~PassageiroDAO();
    void createPassageiro(Passageiro passageiro);
    vector<Passageiro*> findAll();
    Passageiro* findByCpf(string cpf);
    Passageiro* findByNome(string nome);
};



#endif
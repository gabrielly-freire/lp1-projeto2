#ifndef PASSAGEIRO_HPP
#define PASSAGEITO_HPP

#include "Cidade.hpp"

class Passageiro {
    private:
        std::string nome;
        std::string cpf;
        Cidade* localAtual;
    public:
        Passageiro(std::string nome, std::string cpf, Cidade* localAtual);
        std::string getNome();
        std::string getCpf();
        Cidade* getLocalAtual();
        void setLocalAtual(Cidade* local);
};

#endif
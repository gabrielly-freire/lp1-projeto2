#ifndef PASSAGEIRODTO_HPP
#define PASSAGEIRODTO_HPP

#include <string>

class PassageiroDTO{
    private:
        std::string cpf;
        std::string nome;
        std::string local;
    public:
        PassageiroDTO(std::string cpf, std::string nome, std::string local);
        std::string toString();
};

#endif
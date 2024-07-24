#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <string>

class Cidade {
    private:
        int id;
        std::string nome;
    public:
        Cidade(std::string nome);
        Cidade(int id, std::string nome);
        int getId();
        std::string getNome();
};

#endif
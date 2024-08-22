#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <string>

class Cidade {
    private:
        int id;
        std::string nome;
        int visitas;
    public:
        Cidade(std::string nome);
        Cidade(std::string nome, int visitas);
        Cidade(int id, std::string nome, int visitas);
        int getId();
        std::string getNome();
        int getVisitas();
};

#endif
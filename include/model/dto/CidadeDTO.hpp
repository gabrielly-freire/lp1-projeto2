#ifndef CIDADEDTO_HPP
#define CIDADEDTO_HPP

#include <string>

class CidadeDTO {
    private:
        int posicao;
        std::string nome;
        int visitas;
    public:
        CidadeDTO(int posicao, std::string nome, int visitas);
        std::string toString();
};

#endif
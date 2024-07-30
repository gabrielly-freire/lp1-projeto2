#ifndef CIDADEDTO_HPP
#include CIDADEDTO_HPP

#include <string>

class CidadeDTO {
    private:
        int posicao;
        std::string nome;
    public:
        CidadeDTO(int posicao, std::strind nome);
        std::string toString();
};

#endif
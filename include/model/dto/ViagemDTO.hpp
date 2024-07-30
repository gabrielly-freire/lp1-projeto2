#ifndef VIAGEMDTO_HPP
#define VIAGEMDTO_HPP

#include <string>

class ViagemDTO {
    private:
        std::string nomeTransporte;
        std::string nomeCidadeOrigem;
        std::string nomeCidadeDestino;
    public:
        ViagemDTO(std::string nomeTransporte, std::string nomeCidadeOrigem, std::string nomeCidadeDestino);
        std::string toString();
};

#endif
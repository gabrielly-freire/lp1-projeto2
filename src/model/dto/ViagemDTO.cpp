#include "../../../include/model/dto/ViagemDTO.hpp"

ViagemDTO::ViagemDTO(std::string nomeTransporte, std::string nomeCidadeOrigem, std::string nomeCidadeDestino){
    this->nomeTransporte = nomeTransporte;
    this->nomeCidadeOrigem = nomeCidadeOrigem;
    this->nomeCidadeDestino = nomeCidadeDestino;
}

std::string ViagemDTO::toString(){
    return this->nomeTransporte + " - " + this->nomeCidadeOrigem + " - " + this->nomeCidadeDestino + "\n";
}
#include "../../../include/model/dto/TransporteDTO.hpp"

TransporteDTO::TransporteDTO(std::string nome, std::string local){
    this->nome = nome;
    this->local = local;
}

std::string TransporteDTO::toString(){
    return this->nome + " - " + this->local + "\n";
}
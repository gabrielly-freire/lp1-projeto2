#include "../../../include/model/dto/CidadeDTO.hpp"

CidadeDTO::CidadeDTO(int posicao, std::string nome, int visitas){
    this->posicao = posicao;
    this->nome = nome;
    this->visitas = visitas;
}

std::string CidadeDTO::toString(){
    return std::to_string(this->posicao) + " - " + this->nome + " - " + std::to_string(this->visitas) + "\n";
}
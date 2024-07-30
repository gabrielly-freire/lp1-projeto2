#include "../../include/model/dto/CidadeDTO.hpp"

CidadeDTO::CidadeDTO(int posicao, std::strind nome){
    this->posicao = posicao;
    this->nome = nome;
}

std::string CidadeDTO::toString(){
    return this->posicao + " - " + this->nome + "\n";
}
#include "../../include/model/Cidade.hpp"

Cidade::Cidade(std::string nome){
    this->nome = nome;
}

std::string Cidade::getNome(){
    return this->nome;
}

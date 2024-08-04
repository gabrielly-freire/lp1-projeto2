#include "../../include/model/Cidade.hpp"

Cidade::Cidade(std::string nome){
    this->nome = nome;
}

Cidade::Cidade(int id, std::string nome){
    this->id = id;
    this->nome = nome;
}


std::string Cidade::getNome(){
    return this->nome;
}

int Cidade::getId(){
    return this->id;
}
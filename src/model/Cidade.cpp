#include "../../include/model/Cidade.hpp"

Cidade::Cidade(std::string nome){
    this->nome = nome;
}

Cidade::Cidade(std::string nome, int visitas){
    this->nome = nome;
    this->visitas = visitas;
}

Cidade::Cidade(int id, std::string nome, int visitas){
    this->id = id;
    this->nome = nome;
    this->visitas = visitas;
}


std::string Cidade::getNome(){
    return this->nome;
}

int Cidade::getId(){
    return this->id;
}

int Cidade::getVisitas(){
    return this->visitas;
}
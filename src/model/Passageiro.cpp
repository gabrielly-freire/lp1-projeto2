#include "../../include/model/Passageiro.hpp"

Passageiro::Passageiro(std::string nome, std::string cpf, Cidade* localAtual){
    this->nome = nome;
    this->cpf = cpf;
    this->localAtual = localAtual;
}

std::string Passageiro::getNome(){
    return this->nome;
}

std::string Passageiro::getCpf(){
    return this->cpf;
}

Cidade* Passageiro::getLocalAtual(){
    return this->localAtual;
}

void Passageiro::setLocalAtual(Cidade *localAtual){
    this->localAtual = localAtual;
}

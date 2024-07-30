#include "../../include/model/dto/PassageiroDTO.hpp"

PassageiroDTO::PassageiroDTO(std::string cpf, std::string nome, std::string local){
    this->cpf = cpf;
    this->nome = nome;
    this->local = local;
}

std::string PassageiroDTO::toString(){
    return this->cpf + " - " + this->nome + " - " + this->local + "\n";
}
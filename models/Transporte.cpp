#include "../includes/Transporte.hpp"

Transporte::Transporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso,  Cidade* localAtual){
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso = tempo_de_descanso;
    this->localAtual = localAtual;
}

std::string Transporte::getNome(){
    return this->nome;
}

int Transporte::getTipo(){
    return this->tipo;
}

int Transporte::getCapacidade(){
    return this->capacidade;
}

int Transporte::getVelocidade(){
    return this->velocidade;
}

int Transporte::getDistanciaEntreDescansos(){
    return this->distancia_entre_descansos;
}

int Transporte::getTempoDescanso(){
    return this->tempo_de_descanso;
}

int Transporte::getTempoDescansoAtual(){
    return this->tempo_de_descanso_atual;
}

Cidade* Transporte::getLocalAtual(){
    return this->localAtual;
}

void Transporte::setLocalAtual(Cidade* local){
    this->localAtual = local;
}

#include "../../include/model/Transporte.hpp"

Transporte::Transporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso,  int tempo_de_descanso_atual,  Cidade* localAtual){
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso = tempo_de_descanso;
    this->tempo_de_descanso_atual = tempo_de_descanso_atual;
    this->localAtual = localAtual;
}

Transporte::Transporte(int id, std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, int tempo_de_descanso_atual,  Cidade* localAtual){
    this->id = id;
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso = tempo_de_descanso;
    this->tempo_de_descanso_atual = tempo_de_descanso_atual;
    this->localAtual = localAtual;
}

int Transporte::getId(){
    return this->id;
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

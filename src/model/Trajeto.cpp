#include "../../include/model/Trajeto.hpp"

Trajeto::Trajeto(Cidade* origem, Cidade* destino, int tipo, int distancia){
    this->origem = origem;
    this->destino = destino;
    this->tipo = tipo;
    this->distancia = distancia;
}

Trajeto::Trajeto(int id, Cidade* origem, Cidade* destino, int tipo, int distancia){
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->tipo = tipo;
    this->distancia = distancia;
}

int Trajeto::getId(){
    return this->id;
}

Cidade* Trajeto::getOrigem(){
    return this->origem;
}

Cidade* Trajeto::getDestino(){
    return this->destino;
}

int Trajeto::getTipo(){
    return this->tipo;
}

int Trajeto::getDistancia(){
    return this->distancia;
}

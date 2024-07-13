#include "../includes/Trajeto.hpp"

Trajeto::Trajeto(Cidade* origem, Cidade* destino, int tipo, int distancia){
    this->origem = origem;
    this->destino = destino;
    this->tipo = tipo;
    this->distancia = distancia;
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

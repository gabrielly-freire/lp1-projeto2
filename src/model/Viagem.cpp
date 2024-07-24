#include "../../include/model/Viagem.hpp"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino){
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
}

Viagem::Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino){
    this->id = id;
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
}

int Viagem::getId(){
    return this->id;
}

std::vector<Passageiro*> Viagem::getPassageiros(){
    return this->passageiros;
}

Cidade* Viagem::getOrigem(){
    return this->origem;
}

Cidade* Viagem::getDestino(){
    return this->destino;
}

Viagem* Viagem::getProxima(){
    return this->proxima;
}

int Viagem::getHoraEmTransito(){
    return this->horasEmTransito;
}

bool Viagem::isEmAndamento(){
    return this->emAndamento;
}

void iniciarViagem(){
    
}

void avancarHoras(int horas){
    
}

void relatarEstado(){
    
}


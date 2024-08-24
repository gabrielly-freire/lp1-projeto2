#include "../../include/model/Viagem.hpp"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, int emAndamento){
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->trajetos = trajetos;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->statusViagem = emAndamento;
}

Viagem::Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, int emAndamento){
    this->id = id;
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->trajetos = trajetos;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->statusViagem = emAndamento;
}

int Viagem::getId(){
    return this->id;
}

std::vector<Passageiro*> Viagem::getPassageiros(){
    return this->passageiros;
}

std::vector<Trajeto*> Viagem::getTrajetos(){
    return this->trajetos;
}

Transporte* Viagem::getTransporte(){
    return this->transporte;
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

int Viagem::getStatusViagem(){
    return this->statusViagem;
}


void Viagem::setStatusViagem(int status){
    this->statusViagem = status;
}

void iniciarViagem(){
    
}

void Viagem::avancarHoras(int horas){
    horasEmTransito += horas;
}

void relatarEstado(){
    
}
void Viagem::setStatusViagem(int status){
    this->statusViagem = status;
}
int Viagem::getTempoTotalViagem(){
    return this->tempoTotalViagem;
}
void Viagem::setTempoTotalViagem(int valor){
    this->tempoTotalViagem = valor;
}
#include "../../include/model/Viagem.hpp"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento){
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->trajetos = trajetos;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->emAndamento = emAndamento;
}

Viagem::Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento){
    this->id = id;
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->trajetos = trajetos;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->emAndamento = emAndamento;
}

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento){
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->emAndamento = emAndamento;
}

Viagem::Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int horasEmTransito, bool emAndamento){
    this->id = id;
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->horasEmTransito = horasEmTransito;
    this->emAndamento = emAndamento;
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

bool Viagem::isEmAndamento(){
    return this->emAndamento;
}

void iniciarViagem(){
    
}

void avancarHoras(int horas){
    
}

void relatarEstado(){
    
}


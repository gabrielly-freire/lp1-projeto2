#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "Passageiro.hpp"
#include "Transporte.hpp"
#include "Trajeto.hpp"

#include <vector>

class Viagem {
    private:
        int id;
        Transporte* transporte;
        std::vector<Passageiro*> passageiros;
        Cidade* origem;
        Cidade* destino;
        Viagem *proxima;
        int horasEmTransito;
        bool emAndamento;
    public:
        Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
        Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
        
        int getId();
        std::vector<Passageiro*> getPassageiros();
        Cidade* getOrigem();
        Cidade* getDestino();
        Viagem* getProxima();
        int getHoraEmTransito();
        bool isEmAndamento();

        void iniciarViagem();
        void avancarHoras(int horas);
        void relatarEstado();
};

#endif
#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "Passageiro.hpp"
#include "Transporte.hpp"
#include "Trajeto.hpp"

#include <vector>

class Viagem {
    private:
        Transporte* transporte;
        std::vector<Passageiro*> passageiros;
        Cidade* origem;
        Cidade* destino;
        Viagem *proxima;
        int horasEmTransito;
        bool emAndamento;
    public:
        Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
        void iniciarViagem();
        void avancarHoras(int horas);
        void relatarEstado();
        bool isEmAndamento();
};

#endif
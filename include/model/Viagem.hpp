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
        std::vector<Trajeto*> trajetos;
        Cidade* origem;
        Cidade* destino;
        Viagem *proxima;
        int horasEmTransito;
        int statusViagem;
    public:
        Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, int statusViagem);
        Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, std::vector<Trajeto*> trajetos, Cidade* origem, Cidade* destino, int horasEmTransito, int statusViagem);

        int getId();
        std::vector<Passageiro*> getPassageiros();
        std::vector<Trajeto*> getTrajetos();
        Cidade* getOrigem();
        Cidade* getDestino();
        Viagem* getProxima();
        Transporte* getTransporte();
        int getHoraEmTransito();
        int getStatusViagem();

        void iniciarViagem();
        void avancarHoras(int horas);
        void relatarEstado();
};

#endif
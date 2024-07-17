#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "Cidade.hpp"

class Transporte {
    private:
        std::string nome;
        int tipo; // '1' para Aquático, '2' para Terrestre
        int capacidade; // número de passageiros
        int velocidade; // km/h
        int distancia_entre_descansos; // em km
        int tempo_de_descanso; // em horas
        int tempo_de_descanso_atual;  // em horas
        Cidade* localAtual;
    public:
        Transporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso,  Cidade* localAtual);
        std::string getNome();
        int getTipo();
        int getCapacidade();
        int getVelocidade();
        int getDistanciaEntreDescansos();
        int getTempoDescanso();
        int getTempoDescansoAtual();
        Cidade* getLocalAtual();
        void setLocalAtual(Cidade* local);
};

#endif
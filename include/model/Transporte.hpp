#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "Cidade.hpp"

class Transporte {
    private:
        int id;
        std::string nome;
        int tipo;
        int capacidade;
        int velocidade;
        int distancia_entre_descansos;
        int tempo_de_descanso;
        int tempo_de_descanso_atual;
        Cidade* localAtual;
    public:
        Transporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, int tempo_de_descanso_atual, Cidade* localAtual);
        Transporte(int id, std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, int tempo_de_descanso_atual, Cidade* localAtual);
        int getId();
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
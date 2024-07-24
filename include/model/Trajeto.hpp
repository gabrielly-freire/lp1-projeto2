#ifndef TRAJETO_HPP
#define TRAJETO_HPP

#include "Cidade.hpp"

class Trajeto {
    private:
        int id;
        Cidade* origem;
        Cidade* destino;
        int tipo;
        int distancia;
    public:
        Trajeto(Cidade* origem, Cidade* destino, int tipo, int distancia);
        Trajeto(int id, Cidade* origem, Cidade* destino, int tipo, int distancia);
        int getId();
        Cidade* getOrigem();
        Cidade* getDestino();
        int getTipo();
        int getDistancia();
};

#endif
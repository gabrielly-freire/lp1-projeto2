#ifndef TRAJETO_HPP
#define TRAJETO_HPP

#include "Cidade.hpp"

class Trajeto {
    private:
        Cidade* origem;
        Cidade* destino;
        int tipo; // '1' para Aquático, '2' para Terrestre
        int distancia;
    public:
        Trajeto(Cidade* origem, Cidade* destino, int tipo, int distancia);
        Cidade* getOrigem();
        Cidade* getDestino();
        int getTipo();
        int getDistancia();
};

#endif
#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include "Trajeto.hpp"
#include "Cidade.hpp"

using namespace std;
class Grafo
{
private:
    int V;  // Número de vértices
    list<tuple<int, int, int>>* adj; // Lista de adjacências, corrigido para usar tuplas
public:
    Grafo();
    Grafo(int V);
    ~Grafo();  // Destrutor para liberar memória

    void adicionarAresta(std::vector<Trajeto*> trajetos);

    // Ajuste na assinatura do método dfs para incluir destino e tipo de transporte
    vector<Trajeto*> dfs(int partida, int destino, int tipoTransporte, std::vector<Trajeto*> trajetos);

    vector<Trajeto*> melhorRota(vector<tuple<vector<tuple<int, int, int>>, int>> rotas, vector<Trajeto*> trajetos);
};


#endif
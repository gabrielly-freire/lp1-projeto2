#include "../../include/model/Grafo.hpp"

Grafo::Grafo(){}

Grafo::Grafo(int V){
    this->V = V;
    adj = new list<tuple<int, int, int>>[V]; //tupla
}

Grafo::~Grafo()
{
	delete[] adj; // Libera a memória alocada
}

void Grafo::adicionarAresta(vector<Trajeto *> trajetos)
{
	// Adiciona vértice v2 à lista de vértices adjacentes de v1 com a distância e tipo de transporte
	for (size_t i = 0; i < trajetos.size(); i++)
	{
		int origem = trajetos[i]->getOrigem()->getId();
		int destino = trajetos[i]->getDestino()->getId();
		int distancia = trajetos[i]->getDistancia();
		int tipoTransporte = trajetos[i]->getTipo(); // Assumindo que você tem este método

		// Adiciona o destino, a distância, e o tipo de transporte na lista de adjacência
		adj[origem].push_back(make_tuple(destino, distancia, tipoTransporte));
	}
}

//Calcular a menor rota
vector<Trajeto*> Grafo::melhorRota(vector<tuple<vector<tuple<int, int, int>>, int>> rotas, vector<Trajeto*> trajetos){
    vector<Trajeto*> melhorTrajeto;
	vector<tuple<int, int, int>> caminho;

    int menorDistancia = get<1>(rotas[0]);
	caminho = get<0>(rotas[0]);
	for (size_t i = 1; i < rotas.size(); i++)
	{
		if (get<1>(rotas[i]) < menorDistancia)
		{
			menorDistancia = get<1>(rotas[i]);
			caminho = get<0>(rotas[i]);
		}
		
	}

	for (size_t i = 0; i < caminho.size() - 1; i++)
	{
		for (size_t j = 0; j < trajetos.size(); j++)
		{
			if (trajetos[j]->getOrigem()->getId() == get<0>(caminho[i]) && trajetos[j]->getDestino()->getId() == get<0>(caminho[i+1]))
			{
				melhorTrajeto.push_back(trajetos[j]);
			}
			
		}
		
	}

	return melhorTrajeto;

}

vector<Trajeto*> Grafo::dfs(int v, int w, int tipoTransporte, std::vector<Trajeto*> trajetos){
    vector<tuple<int, int, int>> pilha; // Usar vector em vez de stack
	bool visitando[V];
	vector<int> distancia;
	bool regrediu = false;
	vector<tuple<vector<tuple<int, int, int>>, int>> conexoes; // Corrigido o tipo
	vector<Trajeto*> melhorTrajeto;

    // Vetor de visitados
	for (int i = 0; i < V; i++)
	{
		visitando[i] = false;
	}

    // Adiciona o vértice inicial na pilha
	tuple<int, int, int> tupla;
	int distanciaAcumulada = 0;
	
    while (true)
	{
		
		//Visitando os vizinhos não visitados
		if (!visitando[v])
		{
			//marcar como visitado
			visitando[v] = true;	
			pilha.push_back(make_tuple(v, distanciaAcumulada, tipoTransporte)); // insere "v" na pilha
		}

		bool achou = false;
		
		
		list<tuple<int, int, int>>::iterator vz;
		if (regrediu == false)
		{
			// Verificar se algum dos vizinho é o destino
			for (vz = adj[v].begin(); vz != adj[v].end(); vz++)
			{
				
				if (get<0>(*vz) == w && get<2>(*vz) == tipoTransporte)
				{
					
					if (visitando[w] == false)
					{
						visitando[w] = true;
					}
					
					pilha.push_back(make_tuple(get<0>(*vz), get<1>(*vz) + distanciaAcumulada, get<2>(*vz)));
					conexoes.push_back(make_tuple(pilha,get<1>(*vz) + distanciaAcumulada)); // Armazena a pilha e a distância acumulada
					pilha.pop_back();
					break;
				}
			}
		}

		// Resetar regrediu
		if (regrediu)
		{
			regrediu = false;
		}

		list<tuple<int, int, int>>::iterator it;
		// Percorre os vizinhos
		for (it = adj[v].begin(); it != adj[v].end(); it++)
		{

			// Verificar se o próximo vizinho não foi visitado
			if (!visitando[get<0>(*it)] && get<2>(*it) == tipoTransporte)
			{
				achou = true;
				break;
			}
		}

		//Se algum vizinho não tiver sido visitado, visita-lo.
		if (achou)
		{
			v = get<0>(*it);
			distanciaAcumulada += get<1>(*it);
			tipoTransporte = get<2>(*it);
			distancia.push_back(get<1>(*it));
		}

		//Se não, voltar para cidade anterior e, assim, fazer uma nova busca por um vizinho não visitado
		else
		{	
			if (!distancia.empty())
			{
				distanciaAcumulada -= distancia.back();
				distancia.pop_back();
				regrediu = true;
			}
			
			pilha.pop_back();
			
			if (pilha.empty())
			{
				if (conexoes.empty())
				{
					return melhorTrajeto;
				}

				melhorTrajeto = melhorRota(conexoes, trajetos);
				
				return melhorTrajeto;

				break;
			}
			tupla = pilha.back();
			v = get<0>(tupla);
			tipoTransporte = get<2>(tupla);
		}
	}
}
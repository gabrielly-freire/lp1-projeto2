#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include "Trajeto.hpp"
#include "Viagem.hpp"

#include <vector>

class ControladorDeTransito {
    private:
        std::vector<Cidade*> cidades;
        std::vector<Trajeto*> trajetos;
        std::vector<Transporte*> transportes;
        std::vector<Passageiro*> passageiros;
        std::vector<Viagem*> viagens;
    public:
        void cadastrarCidade(std::string nome);
        void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, int tipo, int distancia);
        void cadastrarTransporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
        void cadastrarPassageiro(std::string nome, std::string localAtual);
        void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
        void avancarHoras(int horas);
        void relatarEstado();
};

#endif
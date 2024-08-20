#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include "Trajeto.hpp"
#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include "../connection/Connection.hpp"
#include "../dao/CidadeDAO.hpp"
#include "../dao/PassageiroDAO.hpp"
#include "../dao/TrajetoDAO.hpp"
#include "../dao/TransporteDAO.hpp"
#include "../dao/ViagemDAO.hpp"
#include "../dao/ConsultasDAO.hpp"
#include "dto/CidadeDTO.hpp"
#include "dto/PassageiroDTO.hpp"
#include "dto/TransporteDTO.hpp"
#include "dto/ViagemDTO.hpp"
#include "Grafo.hpp"

#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

class ControladorDeTransito {
    private:
        Connection& conn;
        std::vector<Cidade*> cidades;
        std::vector<Trajeto*> trajetos;
        std::vector<Transporte*> transportes;
        std::vector<Passageiro*> passageiros;
        std::vector<Viagem*> viagens;
        CidadeDAO cidadeDAO;
        PassageiroDAO passageiroDAO;
        TrajetoDAO trajetoDAO;
        TransporteDAO transporteDAO;
        ViagemDAO viagemDAO;
        ConsultasDAO consultasDAO;

    public:
        ControladorDeTransito(Connection& conn);
        void cadastrarCidade();
        void cadastrarTrajeto();
        void cadastrarTransporte();
        void cadastrarPassageiro();
        void cadastrarViagem();
        void verificarRotas();
        void avancarHoras(int horas);
        void iniciarViagem();
        void avancarHoras(std::chrono::system_clock::time_point& timePoint);  
        std::chrono::system_clock::time_point getCurrentTimePoint();
        std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);

        void relatarEstado();
        void gerarRelatorios(int tipo);

        // métodos auxiliares
        bool validarPassageiro(Passageiro* passageiro);
        bool validarCidade(Cidade* cidade);
        bool validarTransporte(Transporte* transporte);
        bool validarTrajeto(Trajeto* trajeto);
        void atualizarListas();
        string para_minusculo(const string& nome);
};

#endif

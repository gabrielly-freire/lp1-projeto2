#include "../../include/model/ControladorDeTransisto.hpp"
#include "../../include/connection/Connection.hpp"
#include "../../include/model/Cidade.hpp"
#include "../../include/model/ControladorDeTransisto.hpp"
#include "../../include/model/Passageiro.hpp"
#include "../../include/model/Trajeto.hpp"
#include "../../include/model/Transporte.hpp"
#include "../../include/model/Viagem.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include "../../include/dao/TrajetoDAO.hpp"
// #include "../../include/dao/PassageiroDAO.hpp"
// #include "../../include/dao/TransporteDAO.hpp"
// #include "../../include/dao/ViagemDAO.hpp"

Connection conn;
CidadeDAO cidadeDAO(conn);
TrajetoDAO trajetoDAO(conn);
// PassageiroDAO passageiroDAO(conn);
// TransporteDAO transporteDAO(conn);
// ViagemDAO viagemDAO(conn);

std::vector<Cidade*> cidades = cidadeDAO.findAll();
std::vector<Trajeto*> trajetos;
std::vector<Transporte*> transportes;
std::vector<Passageiro*> passageiros;
std::vector<Viagem*> viagens;


void ControladorDeTransito::cadastrarCidade(std::string nome){
    Cidade *cidade = new Cidade(nome);

    cidadeDAO.create(*cidade);
    delete cidade;
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, int tipo, int distancia){
    if(cidadeDAO.findByNome(nomeOrigem)->getNome() == ""){
        cidadeDAO.create(nomeOrigem);
    }

    if(cidadeDAO.findByNome(nomeDestino)->getNome() == ""){
        cidadeDAO.create(nomeDestino);
    }

    Cidade* origem = cidadeDAO.findByNome(nomeOrigem);
    Cidade* destino = cidadeDAO.findByNome(nomeDestino);

    Trajeto *trajeto = new Trajeto(origem, destino, tipo, distancia);
    trajetoDAO.create(*trajeto);
    delete trajeto;
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual){
    
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual){
    
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino){
    
}

void ControladorDeTransito::avancarHoras(int horas){
    
}

void ControladorDeTransito::relatarEstado(){

}

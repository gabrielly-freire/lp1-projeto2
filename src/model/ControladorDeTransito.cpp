#include "../../include/model/ControladorDeTransisto.hpp"
#include "../../include/connection/Connection.hpp"
#include "../../include/model/Cidade.hpp"
#include "../../include/model/ControladorDeTransisto.hpp"
#include "../../include/model/Passageiro.hpp"
#include "../../include/model/Trajeto.hpp"
#include "../../include/model/Transporte.hpp"
#include "../../include/model/Viagem.hpp"
#include "../../include/dao/CidadeDAO.hpp"
#include <iostream>

// #include "../../include/dao/PassageiroDAO.hpp"
#include "../../include/dao/TransporteDAO.hpp"
// #include "../../include/dao/ViagemDAO.hpp"

//Connection conn;
//CidadeDAO cidadeDAO(conn);
//TrajetoDAO trajetoDAO(conn);
// PassageiroDAO passageiroDAO(conn);
 //TransporteDAO transporteDAO(conn);
// ViagemDAO viagemDAO(conn);



ControladorDeTransito::ControladorDeTransito(Connection& connection)
    : conn(connection), cidadeDAO(conn),  transporteDAO(conn) {
        atualizarListas(); 
}
void ControladorDeTransito::cadastrarCidade(std::string nome){
    Cidade *cidade = new Cidade(nome);

    cidadeDAO.create(*cidade);
    delete cidade;
}

void ControladorDeTransito::cadastrarCidade(std::string nome){
    Cidade *cidade = new Cidade(nome);

    if(!validarCidade(cidade)){
        std::cout << "Cidade já cadastrada!" << std::endl;
        return;
    }

    cidadeDAO.create(*cidade);
    std::cout << "Cidade cadastrada com sucesso!" << std::endl;
    atualizarListas();
    delete cidade;
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual){
    if(!(tipo == 1 || tipo == 2)){
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }
    if (capacidade <= 0 || velocidade <= 0 || distancia_entre_descansos <= 0 || tempo_de_descanso < 0) {
        std::cout << "Parâmetros inválidos para transporte." << std::endl;
        return;
    }
    Cidade* local = cidadeDAO.findByNome(localAtual);
    if (!local) {
        local = new Cidade(localAtual);
        cidadeDAO.create(*local);
        atualizarListas();
    }
    
    Transporte* transporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local);

    // Cria uma instância de TransporteDAO e chama o método create
    

    TransporteDAO transporteDAO(conn); // Supondo que connection é um membro da classe ControladorDeTransito
    transporteDAO.create(transporte);

    std::cout << "Transporte cadastrado com sucesso!" << std::endl;

    // Limpeza
    delete transporte; // Limpeza do objeto Transpor

    
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual){
    
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino){
    
}

void ControladorDeTransito::avancarHoras(int horas){
    
}

void ControladorDeTransito::relatarEstado(){

}

bool ControladorDeTransito::validarCidade(Cidade* cidade){
    for(int i = 0; i < cidades.size(); i++){
        Cidade* cidadeBanco = cidades[i];
        if(cidadeBanco->getNome() == cidade->getNome()){
            return false;
        }
    }
    return true;
}

void ControladorDeTransito::atualizarListas() {
    cidades = cidadeDAO.findAll();
    transportes = transporteDAO.findAll();
    // trajetos = trajetoDAO.findAll();
}

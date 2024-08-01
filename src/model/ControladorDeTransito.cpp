#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>

ControladorDeTransito::ControladorDeTransito(Connection& connection)
    : conn(connection), cidadeDAO(conn), trajetoDAO(conn), consultasDAO(conn) {
        atualizarListas(); 
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

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, int tipo, int distancia){

    if(!(tipo == 1 || tipo == 2)){
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }

    if(distancia <= 0){
        std::cout << "Distância de viagem inválida!" << std::endl;
        return;
    }

    if(!cidadeDAO.findByNome(nomeOrigem)){
        Cidade novaOrigem(nomeOrigem);
        cidadeDAO.create(novaOrigem);
        atualizarListas();
    }

    if(!cidadeDAO.findByNome(nomeDestino)){
        Cidade novaDestino(nomeDestino);
        cidadeDAO.create(novaDestino);
        atualizarListas();
    }

    Cidade* origem = cidadeDAO.findByNome(nomeOrigem);
    Cidade* destino = cidadeDAO.findByNome(nomeDestino);

    Trajeto *trajeto = new Trajeto(origem, destino, tipo, distancia);
    trajetoDAO.create(*trajeto);
    std::cout << "Trajeto cadastrado com sucesso!" << std::endl;
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

void ControladorDeTransito::gerarRelatorios(int tipo) {
    switch (tipo) {
        case 1: {
            std::vector<PassageiroDTO*> passageirosDTO = consultasDAO.relatorioLocalidadePassagerios();
            for (int i = 0; i < passageirosDTO.size(); i++) {
                PassageiroDTO* passageiroDTO = passageirosDTO[i];
                std::cout << passageiroDTO->toString();
            }
            break;
        }
        case 2: {
            std::vector<TransporteDTO*> transportesDTO = consultasDAO.relatorioLocalidadeTransportes();
            for (int i = 0; i < transportesDTO.size(); i++) {
                TransporteDTO* transporteDTO = transportesDTO[i];
                std::cout << transporteDTO->toString();
            }
            break;
        }
        case 3: {
            std::vector<ViagemDTO*> viagensDTO = consultasDAO.relatorioViagensEmAndamento();
            for (int i = 0; i < viagensDTO.size(); i++) {
                ViagemDTO* viagemDTO = viagensDTO[i];
                std::cout << viagemDTO->toString();
            }
            break;
        }
        case 4: {
            std::vector<CidadeDTO*> cidadesDTO = consultasDAO.relatorioCidadesMaisVisitadas();
            for (int i = 0; i < cidadesDTO.size(); i++) {
                CidadeDTO* cidadeDTO = cidadesDTO[i];
                std::cout << cidadeDTO->toString();
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Opção inválida no Consultas e Relatórios. Tente novamente." << std::endl;
            break;
    }
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
    trajetos = trajetoDAO.findAll();
}

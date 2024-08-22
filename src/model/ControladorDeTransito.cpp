#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>
#include <algorithm> 
#include <cctype> 

using namespace std;

ControladorDeTransito::ControladorDeTransito(Connection &connection)
    : conn(connection), cidadeDAO(conn), trajetoDAO(conn), passageiroDAO(conn), transporteDAO(conn), consultasDAO(conn), viagemDAO(conn) {
    atualizarListas();
}


void ControladorDeTransito::cadastrarCidade() {
    std::string nome;
    cout << "Digite o nome da cidade: ";
    std::getline(std::cin, nome);
    nome = para_minusculo(nome);
    Cidade *cidade = new Cidade(nome, 0);

    if (!validarCidade(cidade)) {
        std::cout << "Cidade já cadastrada!" << std::endl;
        delete cidade;
        return;
    }

    cidadeDAO.create(*cidade);
    std::cout << "Cidade cadastrada com sucesso!" << std::endl;
    atualizarListas();
    delete cidade;
}


void ControladorDeTransito::cadastrarTrajeto() {
    std::string nomeOrigem;
    std::string nomeDestino;
    int tipo;
    int distancia;

    cout << "Digite o nome da cidade de origem: ";
    std::getline(std::cin, nomeOrigem);

    nomeOrigem = para_minusculo(nomeOrigem);

    cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, nomeDestino);

    nomeDestino = para_minusculo(nomeDestino);

    cout << "Digite o tipo de Trajeto (1 = terrestre, 2 = aquático, 3 = aéreo): ";
    cin >> tipo;

    if (!(tipo == 1 || tipo == 2 || tipo == 3)) {
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }

    cout << "Digite a distância do Trajeto: ";
    cin >> distancia;

    if (distancia <= 0) {
        std::cout << "Distância de viagem inválida!" << std::endl;
        return;
    }

    if (!cidadeDAO.findByNome(nomeOrigem)) {
        Cidade novaOrigem(nomeOrigem);
        cidadeDAO.create(novaOrigem);
        atualizarListas();
    }

    if (!cidadeDAO.findByNome(nomeDestino)) {
        Cidade novaDestino(nomeDestino);
        cidadeDAO.create(novaDestino);
        atualizarListas();
    }

    Cidade *origem = cidadeDAO.findByNome(nomeOrigem);
    Cidade *destino = cidadeDAO.findByNome(nomeDestino);

    Trajeto *trajeto = new Trajeto(origem, destino, tipo, distancia);
    if(!validarTrajeto(trajeto)){
        cout << "Já existe esse trajeto!" << endl;
        delete trajeto;
        return;
    }

    trajetoDAO.create(*trajeto);
    std::cout << "Trajeto cadastrado com sucesso!" << std::endl;
    atualizarListas();
    delete trajeto;
}


void ControladorDeTransito::cadastrarTransporte(){
    std::string nomeTransporte;
    std::string localAtualTransporte;
    int tipoTransporte;     
    int capacidadeTransporte;
    int velocidadeTransporte;
    int distanciaDescanso;
    int tempoDescanso;
    int tempoDescansoAtual = 0;

    cout << "Digite o nome do transporte: ";
    std::getline(std::cin, nomeTransporte);


    cout << "Digite número para o tipo do transporte(1 = terrestre, 2 = aquático, 3 = aéreo): ";
    cin >> tipoTransporte;

    if(!(tipoTransporte == 1 || tipoTransporte == 2 || tipoTransporte == 3)){
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }

    cout << "Digite a capacidade do transporte: ";
    cin >> capacidadeTransporte;

    if (capacidadeTransporte <= 0) {
        std::cout << "Capacidade de passageiros inválida." << std::endl;
        return;
    }
    
    cout << "Digite a velocidade do transporte(km/h): ";
    cin >> velocidadeTransporte;

    if (velocidadeTransporte <= 0) {
        std::cout << "Velocidade inválida para o transporte." << std::endl;
        return;
    }

    cout << "Digite a distância percorrida até o descanso(km): ";
    cin >> distanciaDescanso;

    if (distanciaDescanso <= 0) {
        std::cout << "Distância percorrida até o descanso inválida." << std::endl;
        return;
    }

    cout << "Digite o tempo de descanso(em horas): ";
    cin >> tempoDescanso;
    
    if (tempoDescanso < 0) {
        std::cout << "Tempo de descanso inválido." << std::endl;
        return;
    }
    
    std::cin.ignore();
    cout << "Digite o local atual do transporte: ";
    std::getline(std::cin, localAtualTransporte);

    localAtualTransporte = para_minusculo(localAtualTransporte);

    Cidade* local = cidadeDAO.findByNome(localAtualTransporte);
    if (!local) {
        Cidade novo_local(localAtualTransporte);
        cidadeDAO.create(novo_local);
        atualizarListas();
    }
  
    Cidade* novoLocal = cidadeDAO.findByNome(localAtualTransporte);

    Transporte* transporte = new Transporte(nomeTransporte, tipoTransporte, capacidadeTransporte, velocidadeTransporte, distanciaDescanso, tempoDescanso,tempoDescansoAtual, novoLocal);
    if (!validarTransporte(transporte)) {
        std::cout << "Transporte já cadastrado!" << std::endl;
        delete transporte;
        return;
    }

    transporteDAO.create(*transporte);
    std::cout << "Transporte cadastrado com sucesso!" << std::endl;
    atualizarListas();
    delete transporte;
}


void ControladorDeTransito::cadastrarPassageiro() {
    string nome;
    string cpf;
    string local;
    Cidade *localAtual;

    cout << "Digite o nome do passageiro: ";
    getline(cin, nome);


    cout << "Digite o nome do cpf do passageiro: ";
    getline(cin, cpf);

    Passageiro *passageiro_cpf = passageiroDAO.findByCpf(cpf);

    if (passageiro_cpf != nullptr){
        cout << "Cpf já cadastrado." << endl;
    }

    cout << "Digite o nome da cidade atual do passageiro: ";
    getline(cin, local);
    local = para_minusculo(local);
    localAtual = cidadeDAO.findByNome(local);

    if (localAtual == nullptr) {
        cout << "Cidade atual não cadastrada!" << endl;
        return;
    }

    Passageiro *passageiro = new Passageiro(nome, cpf, localAtual);

    if (passageiro == nullptr) {
        cout << "Nenhum registro encontrado!" << endl;
        delete passageiro;
        return;
    }

    if (!validarPassageiro(passageiro)) {
        cout << "Passageiro já cadastrado!" << endl;
        delete passageiro;
        return;
    }

    passageiroDAO.createPassageiro(*passageiro);
    std::cout << "Passageiro cadastrada com sucesso!" << std::endl;

    atualizarListas();

    delete localAtual;
    delete passageiro;

}



std::string ControladorDeTransito::timePointToString(const std::chrono::system_clock::time_point& timePoint) {
    std::time_t now_time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}



void ControladorDeTransito::avancarHoras(std::chrono::system_clock::time_point& timePoint) {
    // Define a duração de uma hora
    std::chrono::hours one_hour(1);

    // Atualiza o timePoint com a nova duração
    timePoint = timePoint + one_hour;
    
}

void ControladorDeTransito::relatarEstado() {
}


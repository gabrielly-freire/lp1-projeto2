#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>

using namespace std;

ControladorDeTransito::ControladorDeTransito(Connection &connection)
    : conn(connection), cidadeDAO(conn), trajetoDAO(conn), passageiroDAO(conn), transporteDAO(conn), consultasDAO(conn), viagemDAO(conn) {
    atualizarListas();
}

void ControladorDeTransito::cadastrarCidade() {
    std::string nome;
    cout << "Digite o nome da cidade: ";
    std::getline(std::cin, nome);
    Cidade *cidade = new Cidade(nome);

    if (!validarCidade(cidade)) {
        std::cout << "Cidade já cadastrada!" << std::endl;
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
    cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, nomeDestino);
    cout << "Digite o tipo de Trajeto (1 = terrestre, 2 = aquático, 3 = aéreo): ";
    cin >> tipo;
    cout << "Digite a distância do Trajeto: ";
    cin >> distancia;

    if (!(tipo == 1 || tipo == 2 || tipo == 3)) {
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }

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
    cout << "Digite a capacidade do transporte: ";
    cin >> capacidadeTransporte;
    cout << "Digite a velocidade do transporte(km/h): ";
    cin >> velocidadeTransporte;
    cout << "Digite a distância percorrida até o descanso(km): ";
    cin >> distanciaDescanso;
    cout << "Digite o tempo de descanso(em horas): ";
    cin >> tempoDescanso;
    std::cin.ignore();
    cout << "Digite o local atual do transporte: ";
    std::getline(std::cin, localAtualTransporte);

    if(!(tipoTransporte == 1 || tipoTransporte == 2 || tipoTransporte == 3)){
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }
    if (capacidadeTransporte <= 0 || velocidadeTransporte <= 0 || distanciaDescanso <= 0 || tempoDescanso < 0 || tempoDescansoAtual < 0) {
        std::cout << "Parâmetros inválidos para transporte." << std::endl;
        return;
    }
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
    cout << "Digite o nome da cidade atual do passageiro: ";
    getline(cin, local);
    localAtual = cidadeDAO.findByNome(local);

    if (localAtual == nullptr) {
        cout << "Cidade atual não cadastrada!" << endl;
        return;
    }

    Passageiro *passageiro = new Passageiro(nome, cpf, localAtual);

    if (passageiro == nullptr) {
        cout << "Nenhum registro encontrado!" << endl;
        return;
    }

    if (!validarPassageiro(passageiro)) {
        cout << "Passageiro já cadastrado!" << endl;
        return;
    }

    passageiroDAO.createPassageiro(*passageiro);
    std::cout << "Passageiro cadastrada com sucesso!" << std::endl;

    atualizarListas();

    delete localAtual;
    delete passageiro;

}

void ControladorDeTransito::cadastrarViagem() {
    std::string nomeTransporte;
    std::vector<std::string> nomesPassageiros;
    std::string nomeOrigem;
    std::string nomeDestino;

    cout << "Digite a cidade de origem: ";
    getline(cin, nomeOrigem);

    if (nomeOrigem == "EmTrânsito"){
        cout << "Cidade de origem não pode ser 'EmTrânsito'" << endl;
        return;
    }

    Cidade* cidadeOrigem = cidadeDAO.findByNome(nomeOrigem);
    if (cidadeOrigem == nullptr) {
        cout << "Cidade não cadastrada no banco de dados" << endl;
        return;
    }

    cout << "Digite a cidade de destino: ";
    getline(cin, nomeDestino);

    Cidade* cidadeDestino = cidadeDAO.findByNome(nomeDestino);
    if (cidadeDestino == nullptr) {
        cout << "Cidade não cadastrada no banco de dados!" << endl;
        return;
    }

    cout << "Digite o nome do transporte: ";
    getline(cin, nomeTransporte);

    Transporte* transporte = transporteDAO.findByNome(nomeTransporte);
    if (transporte == nullptr) {
        cout << "Transporte não cadastrado no banco de dados!" << endl;
        return;
    }

    int capacidade_transporte = transporte->getCapacidade();
    string cpf;
    vector<Passageiro*> passageiros;
    char sim_ou_nao;
    for(int i = 0; i < capacidade_transporte; i++){
        cout << "Digite o cpf do passageiro: " << endl;
        getline(cin, cpf);
        Passageiro* passageiro = passageiroDAO.findByCpf(cpf);
        if (passageiro == nullptr) {
        cout << "Passageiro não cadastrada no banco de dados!" << endl;
        return;
        }
        passageiros.push_back(passageiro);

        cout << "Quer mais passageiros? (S/N)";
        cin >> sim_ou_nao;
        if(sim_ou_nao == 'N' || sim_ou_nao == 'n'){
            break;
        }
        cin.ignore();
    }

    Viagem* viagem = new Viagem(transporte, passageiros, cidadeOrigem, cidadeDestino, 0, false);

    viagemDAO.create(*viagem);
    cout << "Viagem cadastrada com sucesso" << endl;
    
    delete viagem;
    delete cidadeOrigem;
    delete cidadeDestino;
    delete transporte;
}
std::chrono::system_clock::time_point ControladorDeTransito::getCurrentTimePoint() {
    return std::chrono::system_clock::now();
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

bool ControladorDeTransito::validarCidade(Cidade* cidade) {
    for(int i = 0; i < cidades.size(); i++) {
        Cidade* cidadeBanco = cidades[i];
        if(cidadeBanco->getNome() == cidade->getNome()){
            return false;
        }
    }
    return true;
}
bool ControladorDeTransito::validarTransporte(Transporte* transporte) {
    for (int i = 0; i < transportes.size(); i++) {
        if (transportes[i]->getNome() == transporte->getNome()) {
            return false;
        }
    }
    return true;
}


void ControladorDeTransito::atualizarListas() {
    cidades = cidadeDAO.findAll();
    transportes = transporteDAO.findAll();
    trajetos = trajetoDAO.findAll();
    passageiros = passageiroDAO.findAll();
}

bool ControladorDeTransito::validarPassageiro(Passageiro *passageiro) {
    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiro == passageiros[i]) {
            return false;
        }
    }
    return true;
}

bool ControladorDeTransito::validarTransporte(Transporte* transporte) {
    for (int i = 0; i < transportes.size(); i++) {
        if (transportes[i]->getNome() == transporte->getNome()) {
            return false;
        }
    }
    return true;
}


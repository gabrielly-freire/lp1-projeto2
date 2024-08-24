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

std::vector<Viagem*> ControladorDeTransito::avancarHoras(std::chrono::system_clock::time_point& timePoint) {
    system("clear");
    const std::chrono::hours one_hour(1);
    timePoint += one_hour;

    std::vector<Viagem*> viagensAtualizadas;

    for (auto& viagem : viagens) {
        if (viagem->getStatusViagem() == 2) {
            viagensAtualizadas.push_back(viagem);

            double velocidade = viagem->getTransporte()->getVelocidade();
            double distanciaEntreDescansos = viagem->getTransporte()->getDistanciaEntreDescansos();
            double tempoDescanso = viagem->getTransporte()->getTempoDescanso();

            std::vector<Trajeto*> trajetos = viagemDAO.getTrajetos(viagem->getId());
            double tempoTotalViagem = 0.0;
            std::cout << "Trajetos relacionados à viagem " << viagem->getId() << ": ";
            for (auto& trajeto : trajetos) {
                double distanciaTrajeto = trajeto->getDistancia();
                int numeroParadas = static_cast<int>(distanciaTrajeto / distanciaEntreDescansos);
                double tempoViagemSemDescanso = distanciaTrajeto / velocidade;
                double tempoDescansoTotal = numeroParadas * tempoDescanso;
                double tempoTotalTrajeto = tempoViagemSemDescanso + tempoDescansoTotal;

                tempoTotalViagem += tempoTotalTrajeto;

                std::cout << "trajeto: " << trajeto->getOrigem()->getNome() << " -> " << trajeto->getDestino()->getNome();
                if (&trajeto != &trajetos.back()) {
                    std::cout << " | ";
                }
            }

            std::cout << std::endl;
            std::cout << "Tempo atual de viagem: " << viagem->getHoraEmTransito() << " horas" << std::endl;
            std::cout << "Tempo total estimado de viagem: " << static_cast<int>(tempoTotalViagem) << " horas" << std::endl;

            viagem->setTempoTotalViagem(static_cast<int>(tempoTotalViagem));

            // Verifica se a viagem atingiu o tempo total de viagem
            if (viagem->getHoraEmTransito() >= tempoTotalViagem) {
                std::cout << "A viagem " << viagem->getId() << " chegou a seu destino." << std::endl;

                // Incrementa a contagem de visitas para cada cidade de destino nos trajetos
                for (auto& trajeto : trajetos) {
                    int cidadeDestinoId = trajeto->getDestino()->getId();

                    // Obter o número atual de visitas à cidade de destino
                    int visitasAtuais = trajeto->getDestino()->getVisitas();

                    // Incrementar o número de visitas
                    cidadeDAO.setVisitas(cidadeDestinoId, visitasAtuais + 1);
                }

                transporteDAO.setIdCidadeAtual(viagem->getTransporte()->getId(), viagem->getDestino()->getId());
                for (auto& passageiro : viagem->getPassageiros()) {
                    passageiroDAO.setIdCidadeAtual(passageiro->getCpf(), viagem->getDestino()->getId());
                }

                std::cout << "Pressione Enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
                std::cin.get(); // Aguarda o usuário pressionar Enter

                // Alterar o status da viagem para indicar que foi concluída
                viagem->setStatusViagem(3); // 3 representa "concluída" (ou use o valor adequado)
            } else {
                // Avançar o tempo da viagem em uma hora se ela não foi concluída
                viagem->avancarHoras(1);
                std::cout << "Pressione Enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
                std::cin.get(); // Aguarda o usuário pressionar Enter
                system("clear");
            }

            // Atualiza a viagem no banco de dados
            viagemDAO.update(*viagem);
        }
    }

    return viagensAtualizadas;
}

void ControladorDeTransito::relatarEstado() {
}


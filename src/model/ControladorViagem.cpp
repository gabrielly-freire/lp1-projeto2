#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

void ControladorDeTransito::cadastrarViagem()
{
    std::string nomeTransporte;
    std::vector<std::string> nomesPassageiros;
    std::string nomeOrigem;
    std::string nomeDestino;

    vector<Trajeto *> melhorTrajeto;
    int tamanho = static_cast<int>(cidades.size() + 1);
    Grafo *grafo = new Grafo(tamanho);

    cout << "Digite a cidade de origem: ";
    getline(cin, nomeOrigem);

    nomeOrigem = para_minusculo(nomeOrigem);

    if (nomeOrigem == "emtrânsito")
    {
        cout << "Cidade de origem não pode ser 'EmTrânsito'" << endl;
        return;
    }

    Cidade *cidadeOrigem = cidadeDAO.findByNome(nomeOrigem);
    if (cidadeOrigem == nullptr)
    {
        cout << "Cidade não cadastrada no banco de dados" << endl;
        return;
    }

    cout << "Digite a cidade de destino: ";
    getline(cin, nomeDestino);

    nomeDestino = para_minusculo(nomeDestino);

    Cidade *cidadeDestino = cidadeDAO.findByNome(nomeDestino);
    if (cidadeDestino == nullptr)
    {
        cout << "Cidade não cadastrada no banco de dados!" << endl;
        return;
    }

    cout << "Digite o nome do transporte: ";
    getline(cin, nomeTransporte);

    Transporte *transporte = transporteDAO.findByNome(nomeTransporte);
    if (transporte == nullptr)
    {
        cout << "Transporte não cadastrado no banco de dados!" << endl;
        return;
    }

    int capacidade_transporte = transporte->getCapacidade();
    string cpf;
    vector<Passageiro *> passageiros;
    char sim_ou_nao;
    for (int i = 0; i < capacidade_transporte; i++)
    {
        cout << "Digite o cpf do passageiro: ";
        getline(cin, cpf);
        Passageiro *passageiro = passageiroDAO.findByCpf(cpf);
        if (passageiro == nullptr)
        {
            cout << "Passageiro não cadastrada no banco de dados!" << endl;
            return;
        }
        passageiros.push_back(passageiro);

        cout << "Quer mais passageiros? (S/N)";
        cin >> sim_ou_nao;
        if (sim_ou_nao == 'N' || sim_ou_nao == 'n')
        {
            cin.ignore();
            break;
        }
        cin.ignore();
        if (i == capacidade_transporte - 1)
        {
            cout << "Quantidade máxima de passageiros alcançada!" << endl;
        }
    }

    grafo->adicionarAresta(trajetos);
    melhorTrajeto = grafo->dfs(cidadeOrigem->getId(), cidadeDestino->getId(), transporte->getTipo(), trajetos); // Corrigir chamada para incluir tipo

    if (melhorTrajeto.empty())
    {
        cout << "Nenhuma rota encontrada! " << endl;
        delete cidadeOrigem;
        delete cidadeDestino;
        delete transporte;
        return;
    }

    Viagem *viagem = new Viagem(transporte, passageiros, melhorTrajeto, cidadeOrigem, cidadeDestino, 0, 0);

    viagemDAO.create(*viagem);
    cout << "Viagem cadastrada com sucesso!" << endl;

    atualizarListas();

    delete viagem;
    delete cidadeOrigem;
    delete cidadeDestino;
    delete transporte;
    for (size_t i = 0; i < melhorTrajeto.size(); i++)
    {
        delete melhorTrajeto[i];
    }
}




void ControladorDeTransito::verificarRotas(){
    string input;
    int opcao;
    int id;

    do
    {
        //oi
        cout << "VIAGENS CADASTRADAS" << endl;
        for (size_t i = 0; i < viagens.size(); i++)
        {
            cout << "Viagem #" << i+1 << " - Código: " << viagens[i]->getId() << endl;
        }
        
        cout << "Digite o código da viagem que deseja verificar os trajetos: ";
        getline(cin, input);

        try
        {
            opcao = stoi(input);
        }
        catch(const std::exception& e)
        {
            cout << "Opção inválida" << endl;
            break;
        }

        Viagem* viagem = viagemDAO.findById(opcao);

        if (viagem == nullptr)
        {
            cout << "Nenhuma viagem encontrada!" << endl;
            break;
        }
        

        vector<Trajeto*> trajetos = viagem->getTrajetos();

        cout << "A melhor rota da viagem #" << viagem->getId() << " tem os seguintes trajetos: " << endl;
        for (size_t i = 0; i < trajetos.size(); i++)
        {
            cout << "Trajeto #" << i+1 << " - Cidade Origem: " << trajetos[i]->getOrigem()->getNome() << " - Cidade Destino: " << 
            trajetos[i]->getDestino()->getNome() << endl;
        }

        cout << "Digite 1 para continuar verificando: ";
        getline(cin, input);

        try
        {
            opcao = stoi(input);
        }
        catch(const std::exception& e)
        {
            cout<< "Opcao invalida!" << endl;
            break;
        }
        
    } while (opcao == 1);
}
std::chrono::system_clock::time_point ControladorDeTransito::getCurrentTimePoint() {
    return std::chrono::system_clock::now();
}




void ControladorDeTransito::iniciarViagem(){
    string input;
    int opcao;
    
    cout << "=======LISTA DE VIAGEMS======="<<endl;
    for (size_t i = 0; i < viagens.size(); i++)
    {
        cout << "Viagem #" << i+1 << " - Código: " << viagens[i]->getId() << " - Cidade de Origem: " << viagens[i]->getOrigem()->getNome()
        << " - Cidade Destino: " << viagens[i]->getDestino()->getNome() << endl;
    }

    cout << "Digite o código da cidade que deseja iniciar: ";
    getline(cin, input);

    try{
        opcao = stoi(input);
    }
    catch(const std::exception& e)
    {
        cout << "Opcao invalida." << endl;
        return;
    }

    Viagem* viagem = viagemDAO.findById(opcao);
    

    if (viagem == nullptr){
        cout << "Viagem não encontrada!" << endl;
        return;
    }


    if (viagem->getStatusViagem() == 2)
    {
        cout << "Viagem já iniciada!" << endl;
        return;
    }



    Transporte* transporte = transporteDAO.findById(viagem->getTransporte()->getId());

    if (transporte->getLocalAtual()->getId() == 1)
    {
        cout << "Transporte: " << viagem->getTransporte()->getNome() << " está em trânsito." << endl;
        cout << "Não é possível iniciar viagem!" << endl;
        return;
    }

    if (transporte->getLocalAtual()->getId() != viagem->getOrigem()->getId())
    {
        cout << "Transporte: " << viagem->getTransporte()->getNome() << " não está na cidade de origem da viagem." << endl;
        cout << "Não é possível iniciar viagem!" << endl;
        return;
    }


    for (size_t i = 0; i < viagem->getPassageiros().size(); i++){
        
        Passageiro* passageiro = passageiroDAO.findByCpf(viagem->getPassageiros()[i]->getCpf());

        if (viagem->getPassageiros()[i]->getLocalAtual()->getId() == 1)
        {
            cout << "Passageiro: " << viagem->getPassageiros()[i]->getNome() << " está em trânsito." << endl;
            cout << "Não é possível iniciar viagem!" << endl;
            return;
        }
        
        if (passageiro->getLocalAtual()->getId() != viagem->getOrigem()->getId()){
            cout << "Passageiro: " << viagem->getPassageiros()[i]->getNome() << " não está na cidade de origem da viagem." << endl;
            cout << "Não é possível iniciar viagem!" << endl;
            return;
        }

        delete passageiro;
    }

    
    viagemDAO.setStatusViagem(opcao, 2);
    transporteDAO.setIdCidadeAtual(viagem->getTransporte()->getId(), 1);

    for (size_t i = 0; i < viagem->getPassageiros().size(); i++)
    {
        passageiroDAO.setIdCidadeAtual(viagem->getPassageiros()[i]->getCpf(), 1);
    }

   
    
    cout << "Viagem: " << viagem->getId() << " iniciada com sucesso!" << endl;
    atualizarListas();
    delete viagem;
    delete transporte;
}


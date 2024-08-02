#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>

using namespace std;

ControladorDeTransito::ControladorDeTransito(Connection &connection)
    : conn(connection), cidadeDAO(conn), trajetoDAO(conn)
{
    atualizarListas();
}

void ControladorDeTransito::cadastrarCidade(std::string nome)
{
    Cidade *cidade = new Cidade(nome);

    if (!validarCidade(cidade))
    {
        std::cout << "Cidade já cadastrada!" << std::endl;
        return;
    }

    cidadeDAO.create(*cidade);
    std::cout << "Cidade cadastrada com sucesso!" << std::endl;
    atualizarListas();
    delete cidade;
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, int tipo, int distancia)
{

    if (!(tipo == 1 || tipo == 2))
    {
        std::cout << "Tipo de trajeto inválido" << std::endl;
        return;
    }

    if (distancia <= 0)
    {
        std::cout << "Distância de viagem inválida!" << std::endl;
        return;
    }

    if (!cidadeDAO.findByNome(nomeOrigem))
    {
        Cidade novaOrigem(nomeOrigem);
        cidadeDAO.create(novaOrigem);
        atualizarListas();
    }

    if (!cidadeDAO.findByNome(nomeDestino))
    {
        Cidade novaDestino(nomeDestino);
        cidadeDAO.create(novaDestino);
        atualizarListas();
    }

    Cidade *origem = cidadeDAO.findByNome(nomeOrigem);
    Cidade *destino = cidadeDAO.findByNome(nomeDestino);

    Trajeto *trajeto = new Trajeto(origem, destino, tipo, distancia);
    trajetoDAO.create(*trajeto);
    std::cout << "Trajeto cadastrado com sucesso!" << std::endl;
    delete trajeto;
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, int tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual)
{
}

//---------------------------------------------------------------------------------------------------------- TRABALHANDO AQUI ----------------------------------------------------------------------------------------------------------------//
void ControladorDeTransito::cadastrarPassageiro(){
    string nome;
    string cpf;
    string local;
    Cidade *localAtual;

    cout << "Digite o nome do passageiro ";
    getline(cin, nome);
    cout << "Digite o nome do cpf do passageiro: ";
    getline(cin, cpf);
    cout << "Digite o nome da cidade atual do passageiro: ";
    getline(cin, local);
    localAtual = new Cidade(local);

    Passageiro *passageiro = new Passageiro(nome, cpf, localAtual);

}

//---------------------------------------------------------------------------------------------------------- TRABALHANDO AQUI ----------------------------------------------------------------------------------------------------------------//

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino)
{
}

void ControladorDeTransito::avancarHoras(int horas)
{
}

void ControladorDeTransito::relatarEstado()
{
}

bool ControladorDeTransito::validarCidade(Cidade *cidade)
{
    for (int i = 0; i < cidades.size(); i++)
    {
        Cidade *cidadeBanco = cidades[i];
        if (cidadeBanco->getNome() == cidade->getNome())
        {
            return false;
        }
    }
    return true;
}

void ControladorDeTransito::atualizarListas()
{
    cidades = cidadeDAO.findAll();
    trajetos = trajetoDAO.findAll();
}

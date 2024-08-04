#include "util/Util.hpp"
#include "include/model/ControladorDeTransisto.hpp"

#include <iostream>

using namespace std;

int main() {
    int opcao;
    Connection conn;
    ControladorDeTransito controlador(conn);
    std::string nome;
    std::string nomeOrigem;
    std::string nomeDestino;
    int tipo;
    int distancia;
    //std::String Campo Cadastro Transporte:
    std::string nomeTransporte;
    std::string localAtualTransporte;
    //Inteiros Transporte Cadastro:
    int tipoTransporte;     
    int capacidadeTransporte;
    int velocidadeTransporte;
    int distanciaDescanso;
    int tempoDescanso;
    int tempoDescansoAtual = 0;
    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                std::cin.ignore();
                cout << "Digite o nome da cidade: ";
                std::getline(std::cin, nome);
                controlador.cadastrarCidade(nome);
                break;
            case 2:
                std::cin.ignore();
                cout << "Digite o nome da cidade de origem: ";
                std::getline(std::cin, nomeOrigem);
                cout << "Digite o nome da cidade de destino: ";
                std::getline(std::cin, nomeDestino);
                cout << "Digite o tipo de Trajeto: ";
                cin >> tipo;
                cout << "Digite a distância do Trajeto: ";
                cin >> distancia;
                controlador.cadastrarTrajeto(nomeOrigem, nomeDestino, tipo, distancia);
                break;
            case 3:
                 std::cin.ignore();
                cout << "Digite o nome do transporte: ";
                std::getline(std::cin, nomeTransporte);
                cout << "Digite número para o tipo do transporte(1 = terrestre e 2 = aquático): ";
                cin >> tipoTransporte;
                cout << "Digite a capacidade do transporte: ";
                cin >> capacidadeTransporte;
                cout << "Digite a velocidade do transporte(km/h): ";
                cin >> velocidadeTransporte;
                cout << "Digite a distância de descanso(km): ";
                cin >> distanciaDescanso;
                cout << "Digite o tempo de descanso(em horas): ";
                cin >> tempoDescanso;
                std::cin.ignore();
                cout << "Digite o local atual do transporte: ";
                std::getline(std::cin, localAtualTransporte);
                controlador.cadastrarTransporte(nomeTransporte, tipoTransporte, capacidadeTransporte, velocidadeTransporte, distanciaDescanso, tempoDescanso, tempoDescansoAtual , localAtualTransporte);
                break;
            case 4:
                cin.ignore();
                cout << "Cadastrar Passageiro" << endl;
                controlador.cadastrarPassageiro();
                break;
            case 5:
                int subOpcao5;
                do {
                    subOpcao5 = submenu5();
                    switch (subOpcao5) {
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        case 7:
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida no Gestão de Viagens. Tente novamente." << endl;
                            break;
                    }
                } while (subOpcao5 != 0);
                break;
            case 6:
                int subOpcao6;
                do{
                    subOpcao6 = submenu6();
                    controlador.gerarRelatorios(subOpcao6);
                } while (subOpcao6 != 0);
                break;
            case 0:
                cout << "Saindo do sistema controlador de viagens..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
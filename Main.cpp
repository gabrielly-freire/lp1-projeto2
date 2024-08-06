#include "util/Util.hpp"
#include "include/model/ControladorDeTransisto.hpp"

#include <iostream>

using namespace std;

int main() {
    int opcao;
    Connection conn;
    ControladorDeTransito controlador(conn);
    //std::String Campo Cadastro Transporte:
    //Inteiros Transporte Cadastro:
    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                std::cin.ignore();
                controlador.cadastrarCidade();
                break;
            case 2:
                std::cin.ignore();
                controlador.cadastrarTrajeto();
                break;
            case 3:
                std::cin.ignore();
                controlador.cadastrarTransporte();
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
                            std::cin.ignore();
                            controlador.cadastrarViagem();
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
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
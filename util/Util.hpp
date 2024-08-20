#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

using namespace std;

int menu(){
    int op;
    cout << "===== Menu Principal =====" << endl << endl;
    cout << "Selecione uma opção:" << endl;
    cout << "1. Cadastro de Cidades" << endl;
    cout << "2. Cadastro de Trajetos" << endl;
    cout << "3. Cadastro de Transportes" << endl;
    cout << "4. Cadastro de Passageiros" << endl;
    cout << "5. Gestão de Viagens" << endl;
    cout << "6. Consultas e Relatórios" << endl;
    cout << "0. Sair" << endl << endl;
    cout << "Opção: ";
    cin >> op;
    return op;
}

int submenu5(){
    int op;
    cout << "===== Gestão de Viagens =====" << endl << endl;
    cout << "Escolha uma operação:" << endl;
    cout << "1. Cadastrar Viagem" << endl;
    cout << "2. Iniciar viagem" << endl;
    cout << "3. Avançar horas e atualizar estado do sistema" << endl;
    cout << "0. Voltar ao menu principal" << endl << endl;
    cout << "Opção: ";
    cin >> op;
    return op;
}

int submenu6(){
    int op;
    cout << "===== Consultas e Relatórios =====" << endl;
    cout << "Escolha um relatório:" << endl << endl;
    cout << "1. Relatar localização de passageiros (cidade ou em trânsito)" << endl;
    cout << "2. Relatar localização de transportes (cidade ou em trânsito)" << endl;
    cout << "3. Relatar todas as viagens em andamento" << endl;
    cout << "4. Relatar cidades mais visitadas" << endl;
    cout << "0. Voltar ao menu principal" << endl << endl;
    cout << "Opção: ";
    cin >> op;
    return op;
}
#endif
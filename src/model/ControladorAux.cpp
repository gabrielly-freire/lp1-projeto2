#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>
#include <algorithm> 
#include <cctype> 

using namespace std;

bool ControladorDeTransito::validarCidade(Cidade* cidade) {
    for(int i = 0; i < cidades.size(); i++) {
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
    trajetos = trajetoDAO.findAll();
    passageiros = passageiroDAO.findAll();
    viagens = viagemDAO.findAll();
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

bool ControladorDeTransito::validarTrajeto(Trajeto* trajeto) {
    for (int i = 0; i < trajetos.size(); i++) {
        if (trajetos[i]->getOrigem()->getId() == trajeto->getOrigem()->getId() && trajetos[i]->getDestino()->getId() == trajeto->getDestino()->getId() && trajetos[i]->getTipo() == trajeto->getTipo() && trajetos[i]->getDistancia() == trajeto->getDistancia()) {
            return false;
        }
    }
    return true;
}

std::string ControladorDeTransito::para_minusculo(const std::string& nome) {
    std::string resultado = nome;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}
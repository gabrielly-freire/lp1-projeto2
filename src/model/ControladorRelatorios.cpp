#include "../../include/model/ControladorDeTransisto.hpp"
#include <iostream>
#include <algorithm> 
#include <cctype> 

using namespace std;

void ControladorDeTransito::gerarRelatorios(int tipo) {
    switch (tipo) {
        case 1: {
            std::vector<PassageiroDTO*> passageirosDTO = consultasDAO.relatorioLocalidadePassagerios();
            for (int i = 0; i < passageirosDTO.size(); i++) {
                PassageiroDTO* passageiroDTO = passageirosDTO[i];
                std::cout << passageiroDTO->toString();
            }

            if(passageirosDTO.size() == 0){
                std::cout << "Não temos passageiros cadastrados" << std::endl;
            }

            break;
        }
        case 2: {
            std::vector<TransporteDTO*> transportesDTO = consultasDAO.relatorioLocalidadeTransportes();
            for (int i = 0; i < transportesDTO.size(); i++) {
                TransporteDTO* transporteDTO = transportesDTO[i];
                std::cout << transporteDTO->toString();
            }

            if(transportesDTO.size() == 0){
                std::cout << "Não temos transportes cadastrados" << std::endl;
            }

            break;
        }
        case 3: {
            std::vector<ViagemDTO*> viagensDTO = consultasDAO.relatorioViagensEmAndamento();
            for (int i = 0; i < viagensDTO.size(); i++) {
                ViagemDTO* viagemDTO = viagensDTO[i];
                std::cout << "Viagem #"<< (i+1) << ": " << viagemDTO->toString();
            }

            if(viagensDTO.size() == 0){
                std::cout << "Não temos viagens em andamento" << std::endl;
            }

            break;
        }
        case 4: {
            std::vector<CidadeDTO*> cidadesDTO = consultasDAO.relatorioCidadesMaisVisitadas();
            for (int i = 0; i < cidadesDTO.size(); i++) {
                CidadeDTO* cidadeDTO = cidadesDTO[i];
                std::cout << cidadeDTO->toString();
            }

            if(cidadesDTO.size() == 0){
                std::cout << "Não temos cidades cadastradas" << std::endl;
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
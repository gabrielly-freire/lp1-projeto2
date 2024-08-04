#ifndef CONSULTASDAO_HPP
#define CONSULTASDAO_HPP

#include "../connection/Connection.hpp"
#include "mysql/mysql.h"
#include <vector>
#include "../model/dto/CidadeDTO.hpp"
#include "../model/dto/PassageiroDTO.hpp"
#include "../model/dto/TransporteDTO.hpp"
#include "../model/dto/ViagemDTO.hpp"

class ConsultasDAO{
    private:
        Connection& connection;
    public:
        ConsultasDAO(Connection& conn);
        std::vector<PassageiroDTO*> relatorioLocalidadePassagerios();
        std::vector<TransporteDTO*> relatorioLocalidadeTransportes();
        std::vector<CidadeDTO*> relatorioCidadesMaisVisitadas();
        std::vector<ViagemDTO*> relatorioViagensEmAndamento();
};

#endif
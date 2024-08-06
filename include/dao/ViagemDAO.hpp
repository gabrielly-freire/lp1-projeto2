#ifndef VIAGEMDAO_HPP
#define VIAGEMDAO_HPP

#include <mysql/mysql.h>
#include "../connection/Connection.hpp"
#include <vector>
#include "../model/Viagem.hpp"

class ViagemDAO{
    private:
        Connection& connection;
    public:
        ViagemDAO(Connection& connection);
        void create(Viagem viagem);
        Viagem* findById(int id);
        std::vector<Passageiro*> getPassageiros(int id_viagem);
        Viagem* findByOrigem(std::string origem);
        Viagem* findByDestino(std::string destino);
        Viagem* findByTransporte(std::string trasnporte);
};

#endif
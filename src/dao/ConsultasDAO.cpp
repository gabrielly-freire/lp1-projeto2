#include "../../include/dao/ConsultasDAO.hpp"
#include <iostream>

ConsultasDAO::ConsultasDAO(Connection& conn): connection(conn){}

std::vector<PassageiroDTO*> ConsultasDAO::relatorioLocalidadePassagerios(){
    std::vector<PassageiroDTO*> passageiros;
    MYSQL_RES* result;
    MYSQL_ROW row;
    std::string query = "SELECT p.cpf, p.nome, CASE WHEN v.status_viagem = 2 THEN 'em trânsito' ELSE c.nome END "
        "FROM passageiros p LEFT JOIN (SELECT vp.id_passageiro, v.status_viagem FROM passageiros_viagem vp JOIN viagens v ON vp.id_viagem = v.id "
        "WHERE v.status_viagem = 2) v ON p.cpf = v.id_passageiro LEFT JOIN cidades c ON p.id_cidade_atual = c.id;";

    if(mysql_query(connection.getConnection(), query.c_str())){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return passageiros;
    }
    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        std::string cpf = row[0];
        std::string nome = row[1];
        std::string local = row[2];
        PassageiroDTO *passageiro = new PassageiroDTO(cpf, nome, local);
        passageiros.push_back(passageiro);
    }
    mysql_free_result(result);

    return passageiros;
}

std::vector<TransporteDTO*> ConsultasDAO::relatorioLocalidadeTransportes(){
    std::vector<TransporteDTO*> transportes;
    MYSQL_RES* result;
    MYSQL_ROW row;
    std::string query = "SELECT t.nome, CASE WHEN v.status_viagem = 2 THEN 'em trânsito' ELSE c.nome END AS status_localizacao "
        "FROM transportes t LEFT JOIN viagens v ON v.id_transporte = t.id LEFT JOIN cidades c ON t.id_cidade_atual = c.id;";
        
    if(mysql_query(connection.getConnection(), query.c_str())){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return transportes;
    }

    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        std::string nome = row[0];
        std::string local = row[1];

        TransporteDTO *tranporte = new TransporteDTO(nome, local);
        transportes.push_back(tranporte);
    }
    mysql_free_result(result);

    return transportes;
}

std::vector<CidadeDTO*> ConsultasDAO::relatorioCidadesMaisVisitadas(){
    std::vector<CidadeDTO*> cidades;
    MYSQL_RES* result;
    MYSQL_ROW row;
    std::string query = "SELECT nome, visitas FROM cidades ORDER BY visitas DESC";

    if(mysql_query(connection.getConnection(), query.c_str())){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return cidades;
    }

    int posicao = 1;

    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        std::string nomeCidade = row[0];
        int visitas = std::stoi(row[1]);

        if(nomeCidade == "emtrânsito"){
            continue;
        }else{
            CidadeDTO *cidade = new CidadeDTO(posicao, nomeCidade, visitas);
            cidades.push_back(cidade);
            posicao++;
        }

    }

    mysql_free_result(result);
    
    return cidades;
}

std::vector<ViagemDTO*> ConsultasDAO::relatorioViagensEmAndamento(){
    std::vector<ViagemDTO*> viagens;
    MYSQL_RES* result;
    MYSQL_ROW row;
    std::string query = "SELECT t.nome, c_origem.nome, c_destino.nome FROM viagens v JOIN cidades c_origem ON v.id_cidade_origem = c_origem.id "
        "JOIN cidades c_destino on v.id_cidade_destino = c_destino.id JOIN transportes t ON t.id = v.id_transporte "
        "WHERE v.status_viagem = 2"; 

    if(mysql_query(connection.getConnection(), query.c_str())){
        std::cerr << "Erro ao executar a query: " << mysql_error(connection.getConnection()) << std::endl;
        return viagens;
    }
    result = mysql_store_result(connection.getConnection());
    while ((row = mysql_fetch_row(result))) {
        std::string transporte = row[0];
        std::string cidadeOrigem = row[1];
        std::string cidadeDestino = row[2];
        ViagemDTO *viagem = new ViagemDTO(transporte, cidadeOrigem, cidadeDestino);
        viagens.push_back(viagem);
    }
    mysql_free_result(result);

    return viagens;
}

CREATE DATABASE controlador_viagens_db;

USE controlador_viagens_db;

CREATE TABLE IF NOT EXISTS cidades(
    id INT NOT NULL AUTO_INCREMENT,
    nome VARCHAR(255),
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS passageiros(
    cpf VARCHAR(15) NOT NULL,
    nome VARCHAR(50),
    id_cidade_atual INT,
    PRIMARY KEY (cpf),
    FOREIGN KEY(id_cidade_atual) REFERENCES cidades(id)
);

CREATE TABLE IF NOT EXISTS tipo_trajeto(
    id INT NOT NULL,
    descricao VARCHAR(10),
    PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS trajetos(
    id int NOT NULL AUTO_INCREMENT,
    id_cidade_origem INT,
    id_cidade_destino INT,
    id_tipo_trajeto INT,
    distancia INT,
    PRIMARY KEY (id),
    FOREIGN KEY(id_cidade_origem) REFERENCES cidades(id),
    FOREIGN KEY(id_cidade_destino) REFERENCES cidades(id),
    FOREIGN KEY(id_tipo_trajeto) REFERENCES tipo_trajeto(id)
);

CREATE TABLE IF NOT EXISTS transportes(
    id INT NOT NULL AUTO_INCREMENT,
    nome VARCHAR(50),
    capacidade_passageiros INT,
    velocidade INT,
    distancia_entre_descanso INT,
    tempo_de_descanso INT,
    id_cidade_atual INT,
    PRIMARY KEY (id),
    FOREIGN KEY(id_cidade_atual) REFERENCES cidades(id)
);

CREATE TABLE IF NOT EXISTS viagens(
    id int NOT NULL AUTO_INCREMENT,
    id_transporte INT,
    id_cidade_origem INT,
    id_cidade_destino INT,
    horas_em_transito INT,
    em_andamento BOOLEAN,
    id_viagem INT,
    PRIMARY KEY (id)
    FOREIGN KEY(id_transporte) REFERENCES transportes(id),
    FOREIGN KEY(id_cidade_origem) REFERENCES cidades(id),
    FOREIGN KEY(id_cidade_destino) REFERENCES cidades(id),
    FOREIGN KEY(id_viagem) REFERENCES viagens(id)

);

CREATE TABLE IF NOT EXISTS viagens_passegeiros(
    id_viagens_passegeiros INT AUTO_INCREMENT,
    id_viagem INT,
    id_passegeiro VARCHAR(15),
    PRIMARY KEY(id_viagens_passegeiros),
    FOREIGN KEY(id_viagem) REFERENCES viagens(id),
    FOREIGN KEY(id_passegeiro) REFERENCES passageiros(cpf)
);

INSERT INTO tipo_trajeto(id, descricao) VALUES (1, "Terrestre"), (2, "Aquático");

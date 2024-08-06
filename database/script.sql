CREATE DATABASE controlador_viagens_db
DEFAULT CHARACTER SET utf8
DEFAULT COLLATE utf8_general_ci;

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

INSERT INTO tipo_trajeto(id, descricao) VALUES (1, "Terrestre"), (2, "Aquático");

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
    tipo INT,
    capacidade_passageiros INT,
    velocidade INT,
    distancia_entre_descanso INT,
    tempo_de_descanso INT,
    tempo_de_descanso_atual INT,
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
    PRIMARY KEY (id),
    FOREIGN KEY(id_transporte) REFERENCES transportes(id),
    FOREIGN KEY(id_cidade_origem) REFERENCES cidades(id),
    FOREIGN KEY(id_cidade_destino) REFERENCES cidades(id),
);

CREATE TABLE passageiros_Viagem (
  id_viagem INT,
  id_passageiro VARCHAR(15),
  PRIMARY KEY (id_viagem, id_passageiro),
  FOREIGN KEY (id_viagem) REFERENCES viagens(id),
  FOREIGN KEY (id_passageiro) REFERENCES passageiros(cpf)
);
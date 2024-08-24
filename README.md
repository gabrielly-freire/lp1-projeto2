# Sistema controlador de viagens

O sistema controlador de viagens consiste em um projeto da Linguagens de Programação 1 (LP1), disciplina do currículo base do BTI, que tem o objetivo de aplicar os conceitos de programação orientada a objetos em C++ para desenvolver um sistema completo de controle de viagens, consolidando o aprendizado adquirido ao longo do curso.

## Requisitos

### Requisitos Funcionais

- [x] 1. Cadastro de Cidades
- [x] 2. Cadastro de Trajetos
- [x] 3. Cadastro de Transportes
- [x] 4. Cadastro de Passageiros
- [x] 5. Gestão de Viagens
  - [x] Iniciar viagem entre cidades
  - [x] Avançar horas e atualizar estado do sistema
  - [x] Calcular o melhor trajeto entre cidades
- [x] 6. Consultas e Relatórios
  - [x] Relatar onde estão cada pessoa (cidade ou em trânsito, informando origem-destino-transporte)
  - [x] Relatar onde está cada transporte (cidade ou em trânsito)
  - [x] Relatar todas as viagens em andamento
  - [x] Relatar as cidades mais visitadas

### Requisitos Técnicos

- **Interface:** Desenvolver uma interface de linha de comando (CLI) amigável e fácil de usar ou gráfica (opcional).
- **Persistência de Dados:** Os dados devem ser salvos em arquivos de texto ou banco de dados, permitindo que o sistema recupere as informações ao ser reiniciado.
- **Modularização:** O código deve ser organizado em diferentes arquivos para cada classe/módulo.
- **Documentação:** Comentar o código de maneira adequada e fornecer um manual de uso explicando como compilar e executar o sistema.

## Organização do Projeto

```plantex
├── database
├── include
│   ├── connection
│   ├── dao
│   └── model
│       ├── dto
├── Main.cpp
├── Makefile
├── README.md
├── src
│   ├── connection
│   ├── dao
│   └── model
│       ├── dto
└── util
```

### Explicando a organização

- `/database` - Contém o script do banco de dados.
- `/include` - Armazena os cabeçalhos (headers) de todos os arquivos, organizados por categorias para facilitar a manutenção e a leitura do código.
  - `/connection`: Contém o arquivo Connection.hpp, que declara a classe responsável pela conexão com o banco de dados.
  - `/dao`: Contém os cabeçalhos das classes Data Access Object (DAO), que gerenciam a interação com o banco de dados.
  - `/model`: Contém as definições das entidades do projeto.
    - `dto`: Contém as classes Data Transfer Object (DTO), que são utilizadas para transferir dados do banco.
- `/src` - Implementação das classes definidas nos cabeçalhos do diretório include, também organizadas por categorias.
  - `/connection`: Implementação da classe responsável pela conexão com o banco de dados.
  - `/dao`: Implementação das classes que realizam operações no banco de dados, como criação, leitura, atualização e exclusão (CRUD).
  - `/model`: Implementação das entidades do projeto.
    - `/dto`: Implementação das classes DTO.
- `/util`: Contém utilitários, aqui temos os métodos dos menus.
- **Arquivos Raiz**
  - `Main.cpp`: Responsável pela execução da aplicação.
  - `Makefile`: Arquivo utilizado para automatizar a compilação do projeto,
  - `README.md`: Documento que fornece informações sobre o projeto.
  - `.gitignore`: Arquivo que especifica quais arquivos ou diretórios devem ser ignorados pelo sistema de controle de versão Git (Foi muito importante durante o desenvolvimento).

## Instruções de como executar o projeto

1. **Instale o MySQL:**

   ```bash
   sudo apt-get install mysql-server
   ```

2. **Instale o MySQL Connector/C++:**

   ```bash
   sudo apt-get install libmysqlcppconn-dev
   ```

3. **Crie o banco de dados:**

   Execute o [script SQL](database/script.sql):

   ```bash
   mysql -u root -p < script.sql
   ```

    Ou, execute em um SGBD.

4. **Ajuste as propriedades de conexão:**

   Atualize [`Connection.cpp`](src/connection/Connection.cpp) com suas credenciais de banco de dados.

5. **Compile o projeto:**

   ```bash
   make
   ```

6. **Execute o programa:**

   ```bash
   ./main
   ```

<!-- ## Explicação das funcionalidades

1. Cadastro de Cidades
2. Cadastro de Trajetos
3. Cadastro de Transportes
4. Cadastro de Passageiros
5. Gestão de Viagens
   5.1. Iniciar viagem entre cidades
   5.2. Avançar horas e atualizar estado do sistema
   5.3. Calcular o melhor trajeto entre cidades
6. Consultas e Relatórios
  6.1. Relatar onde estão cada pessoa (cidade ou em trânsito, informando origem-destino-transporte)
  6.2. Relatar onde está cada transporte (cidade ou em trânsito)
  6.3. Relatar todas as viagens em andamento
  6.4. Relatar as cidades mais visitadas -->

## Vídeo demonstrativo

[Link do vídeo]()

## Componentes

- [Fernando Silva dos Santos](https://github.com/nandosannn)
- [Francisca Gabrielly Lopes Freire](https://github.com/gabrielly-freire)
- [Gustavo Oliveira de Freitas](https://github.com/Gustaa13)
- [Hendryl Marques Rocha](https://github.com/Ndryl)

-- Nome do Database 
CREATE DATABASE onixlibrary; 

-- Usuário e senha
CREATE USER super_user ENCRYPTED PASSWORD 'carimboatrasado'; 

-- Faz como admin
GRANT ALL ON DATABASE onixlibrary TO super_user; 
ALTER DATABASE onixlibrary OWNER TO super_user; 


-- O DLL FOI FEITO JOGANDO O MODELO LÓGICO NO CHATGPT

-- Tabela: Usuario
CREATE TABLE Usuario (
    id_usuario INT PRIMARY KEY,
    nome VARCHAR(100),
    endereco VARCHAR(255),
    telefone VARCHAR(20)
);

-- Tabela: Biblioteca
CREATE TABLE Biblioteca (
    id_biblioteca INT PRIMARY KEY,
    nome VARCHAR(100),
    endereco VARCHAR(255)
);
 	
-- Tabela: Mídia
CREATE TABLE Midia (
    id_midia INT PRIMARY KEY,
    tipo_midia VARCHAR(50),
    condicao VARCHAR(50),
    id_biblioteca INT,
    FOREIGN KEY (id_biblioteca) REFERENCES Biblioteca(id_biblioteca)
);

-- Tabela: Emprestimo
CREATE TABLE Emprestimo (
    id_emprestimo INT PRIMARY KEY,
    data_emprestimo DATE,
    data_devolucao_prevista DATE,
    data_devolucao DATE,
    id_midia INT,
    id_usuario INT,
    FOREIGN KEY (id_midia) REFERENCES Midia(id_midia),
    FOREIGN KEY (id_usuario) REFERENCES Usuario(id_usuario)
);

-- Tabela: Penalizacao
CREATE TABLE Penalizacao (
    id_penalizacao INT PRIMARY KEY,
    descricao TEXT,
    id_usuario INT,
    id_emprestimo INT,
    FOREIGN KEY (id_usuario) REFERENCES Usuario(id_usuario),
    FOREIGN KEY (id_emprestimo) REFERENCES Emprestimo(id_emprestimo)
);

-- Tabela: Livros
CREATE TABLE Livros (
    id_livro INT PRIMARY KEY,
    titulo VARCHAR(200),
    ISBN VARCHAR(20) UNIQUE,
    numero_paginas INT,
    editora VARCHAR(100),
    data_publicacao DATE,
    FOREIGN KEY (id_livro) REFERENCES Midia(id_midia)
);

-- Tabela: Revistas
CREATE TABLE Revistas (
    id_revista INT PRIMARY KEY,
    titulo VARCHAR(200),
    ISSN VARCHAR(20) UNIQUE,
    periodicidade VARCHAR(50),
    editora VARCHAR(100),
    data_publicacao DATE,
    FOREIGN KEY (id_revista) REFERENCES Midia(id_midia)
);

-- Tabela: DVDs
CREATE TABLE DVDs (
    id_dvd INT PRIMARY KEY,
    titulo VARCHAR(200),
    ISAN VARCHAR(20) UNIQUE,
    duracao INT,
    distribuidora VARCHAR(100),
    data_lancamento DATE,
    FOREIGN KEY (id_dvd) REFERENCES Midia(id_midia)
);

-- Tabela: Artigos
CREATE TABLE Artigos (
    id_artigo INT PRIMARY KEY,
    titulo VARCHAR(200),
    DOI VARCHAR(50) UNIQUE,
    publicadora VARCHAR(100),
    data_publicacao DATE,
    FOREIGN KEY (id_artigo) REFERENCES Midia(id_midia)
);

-- Tabela: Autores
CREATE TABLE Autores (
    id_autor INT PRIMARY KEY,
    nome VARCHAR(100),
    data_nascimento DATE,
    data_falecimento DATE
);

-- Tabela: Autorias
CREATE TABLE Autorias (
    id_autorias INT PRIMARY KEY,
    id_autor INT,
    id_midia INT,
    tipo_midia VARCHAR(50),
    FOREIGN KEY (id_autor) REFERENCES Autores(id_autor),
    FOREIGN KEY (id_midia) REFERENCES Midia(id_midia)
);

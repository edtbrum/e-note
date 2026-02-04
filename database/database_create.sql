-- Sequência de criação do banco e tabelas para e-note no mySQL
--
CREATE DATABASE IF NOT EXISTS db_enote
CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
--
USE db_enote;
--
CREATE TABLE IF NOT EXISTS autor (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    criado_em TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    atualizado_em TIMESTAMP NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB;
--
CREATE TABLE IF NOT EXISTS tag (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    nome VARCHAR(20) NOT NULL UNIQUE
) ENGINE=InnoDB;
--
CREATE TABLE IF NOT EXISTS nota (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    titulo VARCHAR(100) NOT NULL,
    conteudo TEXT NOT NULL,
    criado_em TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    atualizado_em TIMESTAMP NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
    autor_id INT NOT NULL,

    CONSTRAINT fk_autor_nota FOREIGN KEY (autor_id) 
        REFERENCES autor(id) ON DELETE CASCADE ON UPDATE CASCADE,

    INDEX idx_nota_autor (autor_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
--
CREATE TABLE IF NOT EXISTS lembrete (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    data_hora DATETIME NOT NULL,
    ativo BOOLEAN NOT NULL DEFAULT 1,
    nota_id INT NOT NULL,

    CONSTRAINT fk_lembrete_notaid FOREIGN KEY (nota_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE INDEX idx_lembrete_data_ativo ON lembrete (ativo, data_hora);
--
CREATE TABLE IF NOT EXISTS nota_tag (
    nota_id INT NOT NULL,
    tag_id INT NOT NULL,

    PRIMARY KEY (nota_id, tag_id),

    CONSTRAINT fk_notatag_notaid FOREIGN KEY (nota_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_notatag_tagid FOREIGN KEY (tag_id) 
        REFERENCES tag(id) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
--
CREATE TABLE IF NOT EXISTS nota_link (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    tipo ENUM ('interno', 'externo') NOT NULL DEFAULT 'interno',
    url VARCHAR(2048) DEFAULT NULL,
    nota_origem_id INT NOT NULL,
    nota_destino_id INT DEFAULT NULL,

    CONSTRAINT fk_notaorigem_id FOREIGN KEY (nota_origem_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_notadestino_id FOREIGN KEY (nota_destino_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE,

    INDEX idx_nota_origem (nota_origem_id),
    INDEX idx_nota_destino (nota_destino_id),
    INDEX idx_tipo (tipo)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
--
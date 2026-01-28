-- Tabela autor (db_enote)

CREATE TABLE IF NOT EXISTS autor (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    criado_em TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    atualizado_em TIMESTAMP NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB;

-- Inserindo o autor, nesta fase será o único

INSERT INTO autor (nome, email) VALUES ('Eduardo Brum','edtbrum@gmail.com');

-- Consultas

SELECT * FROM autor;
+----+--------------+-------------------+---------------------+---------------+
| id | nome         | email             | criado_em           | atualizado_em |
+----+--------------+-------------------+---------------------+---------------+
|  1 | Eduardo Brum | edtbrum@gmail.com | 2026-01-28 18:07:14 | NULL          |
+----+--------------+-------------------+---------------------+---------------+


-- Tabela autor (db_enote)

CREATE TABLE IF NOT EXISTS autor (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    criado_em TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    atualizado_em TIMESTAMP NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB;

-- Descrição da tabela

DESCRIBE autor;
+---------------+--------------+------+-----+-------------------+-----------------------------+
| Field         | Type         | Null | Key | Default           | Extra                       |
+---------------+--------------+------+-----+-------------------+-----------------------------+
| id            | int          | NO   | PRI | NULL              | auto_increment              |
| nome          | varchar(100) | NO   |     | NULL              |                             |
| email         | varchar(100) | NO   | UNI | NULL              |                             |
| criado_em     | timestamp    | NO   |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED           |
| atualizado_em | timestamp    | YES  |     | NULL              | on update CURRENT_TIMESTAMP |
+---------------+--------------+------+-----+-------------------+-----------------------------+

-- Inserindo o autor, nesta fase será o único

INSERT INTO autor (nome, email) VALUES ('Eduardo Brum','edtbrum@gmail.com');

-- Consultas

SELECT * FROM autor;
+----+--------------+-------------------+---------------------+---------------+
| id | nome         | email             | criado_em           | atualizado_em |
+----+--------------+-------------------+---------------------+---------------+
|  1 | Eduardo Brum | edtbrum@gmail.com | 2026-01-28 18:07:14 | NULL          |
+----+--------------+-------------------+---------------------+---------------+


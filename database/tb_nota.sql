-- Tabela nota (tb_enote)

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
) ENGINE=InnoDB 
DEFAULT CHARSET=utf8mb4 
COLLATE=utf8mb4_unicode_ci;

-- Apagar tabela (cuidado!)

DROP TABLE IF EXISTS nota;

-- Descrição da tabela

DESCRIBE nota;
+---------------+--------------+------+-----+-------------------+-----------------------------+
| Field         | Type         | Null | Key | Default           | Extra                       |
+---------------+--------------+------+-----+-------------------+-----------------------------+
| id            | int          | NO   | PRI | NULL              | auto_increment              |
| titulo        | varchar(100) | NO   |     | NULL              |                             |
| conteudo      | text         | NO   |     | NULL              |                             |
| criado_em     | timestamp    | NO   |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED           |
| atualizado_em | timestamp    | YES  |     | NULL              | on update CURRENT_TIMESTAMP |
| autor_id      | int          | NO   | MUL | NULL              |                             |
+---------------+--------------+------+-----+-------------------+-----------------------------+

-- visualizar index

SELECT
    index_name,
    column_name,
    seq_in_index,
    non_unique
FROM information_schema.statistics
WHERE table_schema = 'db_enote'
  AND table_name = 'nota'
ORDER BY index_name, seq_in_index;
+----------------+-------------+--------------+------------+
| INDEX_NAME     | COLUMN_NAME | SEQ_IN_INDEX | NON_UNIQUE |
+----------------+-------------+--------------+------------+
| idx_nota_autor | autor_id    |            1 |          1 |
| PRIMARY        | id          |            1 |          0 |
+----------------+-------------+--------------+------------+

-- Inserir nota

INSERT INTO nota (titulo,conteudo,autor_id) VALUES 
("Primeiro titulo","Esta nota e de teste.",1);

INSERT INTO nota (titulo,conteudo,autor_id) VALUES 
("Segundo titulo","Esta nota possui um link para Primeiro Titulo.",1);
+----+----------------+------------------------------------------------+---------------------+---------------------+----------+
| id | titulo         | conteudo                                       | criado_em           | atualizado_em       | autor_id |
+----+----------------+------------------------------------------------+---------------------+---------------------+----------+
|  1 | Primeira nota  | Esse nota aponta para o Google.                | 2026-01-29 09:38:08 | 2026-01-30 09:37:37 |        1 |
| 10 | Segundo titulo | Esta nota possui um link para Primeiro Titulo. | 2026-01-30 09:32:39 | NULL                |        1 |
+----+----------------+------------------------------------------------+---------------------+---------------------+----------+

-- Alterar nota

UPDATE nota SET 
    titulo = "Segunda nota",
    conteudo = "Esse nota aponta para a Primeira nota."
WHERE id = 10;

-- Consultas

SELECT 
    n.id,
    n.titulo,
    n.conteudo,
    n.criado_em,
    n.atualizado_em,
    a.nome AS autor
FROM nota n
JOIN autor a ON a.id = n.autor_id;
+----+---------------+--------------------------------+---------------------+---------------------+--------------+
| id | titulo        | conteudo                       | criado_em           | atualizado_em       | autor        |
+----+---------------+--------------------------------+---------------------+---------------------+--------------+
|  1 | Primeira nota | Conteudo da nota foi alterado. | 2026-01-29 09:38:08 | 2026-01-29 09:39:03 | Eduardo Brum |
+----+---------------+--------------------------------+---------------------+---------------------+--------------+

-- query para serviço

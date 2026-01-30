-- Tabela lembrete (db_enote)

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

) ENGINE=InnoDB 
DEFAULT CHARSET=utf8mb4 
COLLATE=utf8mb4_unicode_ci;

-- Descreve tabelas

DESCRIBE nota_link;
+-----------------+---------------------------+------+-----+---------+----------------+
| Field           | Type                      | Null | Key | Default | Extra          |
+-----------------+---------------------------+------+-----+---------+----------------+
| id              | int                       | NO   | PRI | NULL    | auto_increment |
| tipo            | enum('interno','externo') | NO   | MUL | interno |                |
| url             | varchar(2048)             | YES  |     | NULL    |                |
| nota_origem_id  | int                       | NO   | MUL | NULL    |                |
| nota_destino_id | int                       | YES  | MUL | NULL    |                |
+-----------------+---------------------------+------+-----+---------+----------------+

-- Inserindo registros

INSERT INTO nota_link (tipo, url, nota_origem_id, nota_destino_id) 
VALUES ('externo', 'https://www.google.com', 1, NULL);

INSERT INTO nota_link (tipo, url, nota_origem_id, nota_destino_id) 
VALUES ('interno', NULL, 10, 1);

+----+---------+------------------------+----------------+-----------------+
| id | tipo    | url                    | nota_origem_id | nota_destino_id |
+----+---------+------------------------+----------------+-----------------+
|  1 | externo | https://www.google.com |              1 |            NULL |
|  2 | interno | NULL                   |             10 |               1 |
+----+---------+------------------------+----------------+-----------------+

-- Consulta

SELECT 
    nl.id,
    nl.tipo,
    nl.url,
    nl.nota_origem_id,
    no.titulo AS origem,
    nl.nota_destino_id,
    nd.titulo AS destino
FROM nota_link nl
JOIN nota no ON no.id = nl.nota_origem_id
LEFT JOIN nota nd ON nd.id = nl.nota_destino_id;
+----+---------+------------------------+----------------+---------------+-----------------+---------------+
| id | tipo    | url                    | nota_origem_id | origem        | nota_destino_id | destino       |
+----+---------+------------------------+----------------+---------------+-----------------+---------------+
|  1 | externo | https://www.google.com |              1 | Primeira nota |            NULL | NULL          |
|  2 | interno | NULL                   |             10 | Segunda nota  |               1 | Primeira nota |
+----+---------+------------------------+----------------+---------------+-----------------+---------------+

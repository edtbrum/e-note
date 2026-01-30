-- Tabela lembrete (db_enote)

CREATE TABLE IF NOT EXISTS lembrete (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    data_hora DATETIME NOT NULL,
    ativo BOOLEAN NOT NULL DEFAULT 1,
    nota_id INT NOT NULL,

    CONSTRAINT fk_lembrete_notaid FOREIGN KEY (nota_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB 
DEFAULT CHARSET=utf8mb4;

CREATE INDEX idx_lembrete_data_ativo ON lembrete (ativo, data_hora);

-- Descreve tabelas

DESCRIBE lembrete;
+-----------+------------+------+-----+---------+----------------+
| Field     | Type       | Null | Key | Default | Extra          |
+-----------+------------+------+-----+---------+----------------+
| id        | int        | NO   | PRI | NULL    | auto_increment |
| data_hora | datetime   | NO   |     | NULL    |                |
| ativo     | tinyint(1) | NO   | MUL | 1       |                |
| nota_id   | int        | NO   | MUL | NULL    |                |
+-----------+------------+------+-----+---------+----------------+

-- Inserindo lembrete

INSERT INTO lembrete (data_hora,nota_id) VALUES ('2026-03-17 14:36:00',1);
+----+---------------------+-------+---------+
| id | data_hora           | ativo | nota_id |
+----+---------------------+-------+---------+
|  1 | 2026-03-17 14:36:00 |     1 |       1 |
+----+---------------------+-------+---------+

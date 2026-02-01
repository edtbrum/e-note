-- Tabela tag (db_enote)

CREATE TABLE IF NOT EXISTS tag (
    id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    nome VARCHAR(20) NOT NULL UNIQUE
) ENGINE=InnoDB 
DEFAULT CHARSET=utf8mb4;

-- Tabela nota_tag (db_enote)

CREATE TABLE IF NOT EXISTS nota_tag (
    nota_id INT NOT NULL,
    tag_id INT NOT NULL,

    PRIMARY KEY (nota_id, tag_id),

    CONSTRAINT fk_notatag_notaid FOREIGN KEY (nota_id) 
        REFERENCES nota(id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_notatag_tagid FOREIGN KEY (tag_id) 
        REFERENCES tag(id) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4;

GRANT SELECT, INSERT, DELETE ON db_enote.tag TO 'app_user';
GRANT SELECT, INSERT, DELETE ON db_enote.nota_tag TO 'app_user';

-- Tag não pode ser renomeada
-- Relação nota-tag só pode ser criada ou removida

-- Descreve tabelas

DESCRIBE tag;
+-------+-------------+------+-----+---------+----------------+
| Field | Type        | Null | Key | Default | Extra          |
+-------+-------------+------+-----+---------+----------------+
| id    | int         | NO   | PRI | NULL    | auto_increment |
| nome  | varchar(20) | NO   | UNI | NULL    |                |
+-------+-------------+------+-----+---------+----------------+

SHOW FULL COLUMNS FROM tag;
+-------+-------------+--------------------+------+-----+---------+----------------+---------------------------------+---------+
| Field | Type        | Collation          | Null | Key | Default | Extra          | Privileges                      | Comment |
+-------+-------------+--------------------+------+-----+---------+----------------+---------------------------------+---------+
| id    | int         | NULL               | NO   | PRI | NULL    | auto_increment | select,insert,update,references |         |
| nome  | varchar(20) | utf8mb4_0900_ai_ci | NO   | UNI | NULL    |                | select,insert,update,references |         |
+-------+-------------+--------------------+------+-----+---------+----------------+---------------------------------+---------+

DESCRIBE nota_tag;
+---------+------+------+-----+---------+-------+
| Field   | Type | Null | Key | Default | Extra |
+---------+------+------+-----+---------+-------+
| nota_id | int  | NO   | PRI | NULL    |       |
| tag_id  | int  | NO   | PRI | NULL    |       |
+---------+------+------+-----+---------+-------+

-- Inserindo dados

INSERT INTO tag (nome) VALUES ("Teste");
+----+-------+
| id | nome  |
+----+-------+
|  1 | Teste |
+----+-------+

INSERT INTO nota_tag (nota_id, tag_id) VALUES (1,1);
+---------+--------+
| nota_id | tag_id |
+---------+--------+
|       1 |      1 |
+---------+--------+

-- Consulta

SELECT t.nome FROM tag t
JOIN nota_tag nt ON nt.tag_id = t.id
WHERE nt.nota_id = 1;
+-------+
| nome  |
+-------+
| Teste |
+-------+


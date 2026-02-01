-- logar já usando db_enote com usuário dev
-- mysql -u dev -p db_enote

CREATE DATABASE IF NOT EXISTS db_enote
CHARACTER SET utf8mb4
COLLATE utf8mb4_general_ci;

USE db_enote;

SHOW DATABASES;
SHOW TABLES;

SELECT TABLE_NAME, TABLE_TYPE, ENGINE, TABLE_ROWS, CREATE_TIME 
FROM information_schema.TABLES WHERE TABLE_SCHEMA = 'db_enote';
+------------+------------+--------+------------+---------------------+
| TABLE_NAME | TABLE_TYPE | ENGINE | TABLE_ROWS | CREATE_TIME         |
+------------+------------+--------+------------+---------------------+
| autor      | BASE TABLE | InnoDB |          2 | 2026-01-28 18:02:31 |
| lembrete   | BASE TABLE | InnoDB |          0 | 2026-01-29 17:54:54 |
| nota       | BASE TABLE | InnoDB |          0 | 2026-01-29 09:31:09 |
| nota_link  | BASE TABLE | InnoDB |          0 | 2026-01-30 09:26:57 |
| nota_tag   | BASE TABLE | InnoDB |          0 | 2026-01-29 16:48:15 |
| tag        | BASE TABLE | InnoDB |          0 | 2026-01-29 16:48:03 |
+------------+------------+--------+------------+---------------------+

SHOW VARIABLES LIKE 'default_storage_engine';
+------------------------+--------+
| Variable_name          | Value  |
+------------------------+--------+
| default_storage_engine | InnoDB |
+------------------------+--------+

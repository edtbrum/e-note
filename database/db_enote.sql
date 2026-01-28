-- logar já usando db_enote
-- mysql -u dev -p db_enote

CREATE DATABASE IF NOT EXISTS db_enote;

USE db_enote;

SHOW DATABASES;
SHOW TABLES;

SELECT TABLE_NAME, TABLE_TYPE, ENGINE, TABLE_ROWS, CREATE_TIME 
FROM information_schema.TABLES WHERE TABLE_SCHEMA = 'db_enote';


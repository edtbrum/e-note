#include "dao/cAutorDAO.h"
#include "domain/cAutor.h"
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

cAutorDAO::cAutorDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cAutorDAO::get() {
    return m_conn;
}

int cAutorDAO::insert(const cAutor& autor) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO autor (nome, email) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, autor.nome());
        stmt->setString(2, autor.email());
        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: [cAutorDAO] Insert falhou (rows = 0)");
        }

        std::unique_ptr<sql::Statement> stmtid(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtid->executeQuery("SELECT LAST_INSERT_ID()"));
        if (res->next()) {
            return res->getInt(1);
        }

        throw std::runtime_error("Error: [cAutorDAO] LAST_INSERT_ID falhou");
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: [cAutorDAO] " + std::string(e.what()));
    }
}

void cAutorDAO::update(cAutor& autor) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "UPDATE autor SET nome = ?, email = ? WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, autor.nome());
        stmt->setString(2, autor.email());
        stmt->setInt(3, autor.identifier());
        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Update falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

cAutor cAutorDAO::findbyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT * FROM autor WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cAutor n_autor;
            n_autor.setid(res->getInt("id"));
            n_autor.setnome(res->getString("nome"));
            n_autor.setemail(res->getString("email"));
            return n_autor;
        }

        throw std::runtime_error("Error: Procura falhou, id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

std::vector<cAutor> cAutorDAO::list() {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT id, nome, email FROM autor";
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(ssql));
        std::vector<cAutor> autores;
        while (res->next()) {
            cAutor autor;
            autor.setid(res->getInt("id"));
            autor.setnome(res->getString("nome"));
            autor.setemail(res->getString("email"));
            autores.push_back(autor);
        }

        if (autores.empty()) {
            throw std::runtime_error("Error: Tabela autor sem registros");
        }

        return autores;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cAutorDAO::deletebyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "DELETE FROM autor WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        if (stmt->executeUpdate() == 0) {
            throw std::runtime_error("Error: [cAutorDAO] Delete falhou, id = " + std::to_string(id));
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

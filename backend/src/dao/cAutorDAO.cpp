#include "dao/cAutorDAO.h"
#include "dao/IAutorDAO.h"
#include "domain/cAutor.h"
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <stdexcept>

cAutorDAO::cAutorDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cAutorDAO::get() {
    return m_conn;
}

void cAutorDAO::insert(cAutor& autor) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO autor (nome, email) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, autor.nome());
        stmt->setString(2, autor.email());
        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Insert falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
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

cAutor cAutorDAO::find(cAutor& autor, eSearchAuthor type) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql;
        if (type == eSearchAuthor::AuthorID) { ssql = "SELECT * FROM autor WHERE id = ?"; }
        if (type == eSearchAuthor::AuthorName) { ssql = "SELECT * FROM autor WHERE nome = ?"; }
        if (type == eSearchAuthor::AuthorEmail) { ssql = "SELECT * FROM autor WHERE email = ?"; }
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        if (type == eSearchAuthor::AuthorID) { stmt->setInt(1, autor.identifier()); }
        if (type == eSearchAuthor::AuthorName) { stmt->setString(1, autor.nome()); }
        if (type == eSearchAuthor::AuthorEmail) { stmt->setString(1, autor.email()); }

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cAutor n_autor;
            n_autor.setid(res->getInt("id"));
            n_autor.setnome(res->getString("nome"));
            n_autor.setemail(res->getString("email"));
            return n_autor;
        }

        throw std::runtime_error("Error: Procura falhou (tabela autor)");
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

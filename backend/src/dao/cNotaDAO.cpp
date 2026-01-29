#include "dao/cNotaDAO.h"
#include "domain/cNota.h"
#include "util/uTimePoint.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <stdexcept>
#include <string>

cNotaDAO::cNotaDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cNotaDAO::get() {
    return m_conn;
}

void cNotaDAO::insert(cNota& nota) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO nota (titulo,conteudo,autor_id) VALUES (?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nota.titulo());
        stmt->setString(2, nota.conteudo());
        stmt->setInt(3, nota.autor_id());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Insert falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cNotaDAO::update(cNota& nota) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "UPDATE nota SET titulo = ?, conteudo = ? WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nota.titulo());
        stmt->setString(2, nota.conteudo());
        stmt->setInt(3, nota.identifier());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Update falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

cNota cNotaDAO::findbyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT * FROM nota WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cNota nota;
            nota.setidentifier(id);
            nota.settitulo(res->getString("titulo"));
            nota.setconteudo(res->getString("conteudo"));
            nota.setcriado_em(from_string(res->getString("criado_em")));
            nota.setatualizado_em(from_string(res->getString("atualizado_em")));
            nota.setautor_id(res->getInt("autor_id"));
            return nota;
        }

        throw std::runtime_error("Error: [nota] Register not found by id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

#include "dao/cNotaDAO.h"
#include "domain/cNota.h"
#include "util/uTimePoint.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <cppconn/statement.h>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

cNotaDAO::cNotaDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cNotaDAO::get() {
    return m_conn;
}

int cNotaDAO::insert(const cNota& nota) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO nota (titulo,conteudo,autor_id) VALUES (?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nota.titulo());
        stmt->setString(2, nota.conteudo());
        stmt->setInt(3, nota.autor_id());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: [cNotaDAO] Insert falhou");
        }

        std::unique_ptr<sql::Statement> stmtid(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtid->executeQuery("SELECT LAST_INSERT_ID()"));
        if (res->next()) {
            return res->getInt(1);
        }

        throw std::runtime_error("Error: [cNotaDAO] LAST_INSERT_ID falhou");
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cNotaDAO::update(const cNota& nota) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "UPDATE nota SET titulo = ?, conteudo = ? WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nota.titulo());
        stmt->setString(2, nota.conteudo());
        stmt->setInt(3, nota.identifier());
        int rows = stmt->executeUpdate();
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
            if (!res->isNull("atualizado_em")) {
                nota.setatualizado_em(from_string(res->getString("atualizado_em")));
            }
            else {
                nota.setatualizado_em(std::nullopt);
            }
            
            nota.setautor_id(res->getInt("autor_id"));
            return nota;
        }

        throw std::runtime_error("Error: [cNotaDAO] Register not found id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

std::vector<cNota> cNotaDAO::find() {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT * FROM nota";
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(ssql));
        std::vector<cNota> notas;
        while (res->next()) {
            cNota nota;
            nota.setidentifier(res->getInt("id"));
            nota.settitulo(res->getString("titulo"));
            nota.setconteudo(res->getString("conteudo"));
            nota.setcriado_em(from_string(res->getString("criado_em")));
            if (!res->isNull("atualizado_em")) {
                nota.setatualizado_em(from_string(res->getString("atualizado_em")));
            }
            else {
                nota.setatualizado_em(std::nullopt);
            }
            
            nota.setautor_id(res->getInt("autor_id"));
            notas.push_back(nota);
        }

        if (notas.empty()) {
            throw std::runtime_error("Error: [cNotaDAO] Nenhuma nota encontrada");
        }

        return notas;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cNotaDAO::deletebyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "DELETE FROM nota WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        if (stmt->executeUpdate() == 0) {
            throw std::runtime_error("Error: [cNotaDAO] Delete falhou, id = " + std::to_string(id));
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

int cNotaDAO::verifynota(int nota_id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT COUNT(*) AS total FROM nota_link WHERE nota_destino_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, nota_id);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            return res->getInt("total");
        }

        return 0;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

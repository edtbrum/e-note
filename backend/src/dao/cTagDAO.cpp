#include "cTagDAO.h"
#include "domain/cTag.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

cTagDAO::cTagDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cTagDAO::get() {
    return m_conn;
}

int cTagDAO::insert(const std::string nome) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO tag (nome) VALUES (?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nome);

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: [cTagDAO] Insert falhou");
        }

        std::unique_ptr<sql::Statement> stmtid(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtid->executeQuery("SELECT LAST_INSERT_ID()"));
        if (res->next()) {
            return res->getInt(1);
        }

        throw std::runtime_error("Error: [cTagDAO] LAST_INSERT_ID falhou");
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

cTag cTagDAO::findbyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT id, nome FROM tag WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cTag tag;
            tag.setidentifier(res->getInt("id"));
            tag.setnome(res->getString("nome"));
            return tag;
        }

        throw std::runtime_error("Error: [cTagDAO] Not found id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

std::vector<cTag> cTagDAO::list() {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT id, nome FROM tag";
        std::unique_ptr<sql::Statement> stmtid(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtid->executeQuery(ssql));
        std::vector<cTag> tags;
        while (res->next()) {
            cTag tag;
            tag.setidentifier(res->getInt("id"));
            tag.setnome(res->getString("nome"));
            tags.push_back(tag);
        }

        if (tags.empty()) {
            throw std::runtime_error("Error: [cTagDAO] Listagem falhou");
        }

        return tags;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cTagDAO::deletebyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "DELETE FROM tag WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        if (stmt->executeUpdate() == 0) {
            throw std::runtime_error("Error: [cTagDAO] Delete falhou, id = " + std::to_string(id));
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

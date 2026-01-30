#include "cTagDAO.h"
#include "domain/cTag.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <stdexcept>
#include <string>

cTagDAO::cTagDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cTagDAO::get() {
    return m_conn;
}

void cTagDAO::insert(cTag tag) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO tag (nome) VALUES (?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, tag.nome());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Insert falhou");
        }
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
            tag.setidentifier(id);
            tag.setnome(res->getString("nome"));
            return tag;
        }

        throw std::runtime_error("Error: Register not found by id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

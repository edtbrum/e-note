#include "cNotaTagDAO.h"
#include "domain/cNotaTag.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

cNotaTagDAO::cNotaTagDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cNotaTagDAO::get() {
    return m_conn;
}

void cNotaTagDAO::insert(cNotaTag& ntag) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO nota_tag (nota_id, tag_id) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, ntag.nota_id());
        stmt->setInt(2, ntag.tag_id());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Insert falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cNotaTagDAO::insertBatch(const std::vector<cNotaTag>& tags, int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO nota_tag (nota_id, tag_id) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        
        for (const auto& tag : tags) {
            stmt->clearParameters();
            stmt->setInt(1, notaid);
            stmt->setInt(2, tag.tag_id());

            int rows = stmt->executeUpdate();
            if (!rows) {
                throw std::runtime_error("Error: [cNotaTagDAO] Insert falhou");
            }
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

std::vector<cNotaTag> cNotaTagDAO::findbynotaid (int id) {
    std::vector<cNotaTag> ntag;
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT nota_id, tag_id FROM nota_tag WHERE nota_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        while (res->next()) {
            cNotaTag t;
            t.setnota_id(res->getInt("nota_id"));
            t.settag_id(res->getInt("tag_id"));
            ntag.push_back(t);
        }

        return ntag;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cNotaTagDAO::deletebyid(const cNotaTag& ntag) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "DELETE FROM nota_tag WHERE nota_id = ? AND tag_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, ntag.nota_id());
        stmt->setInt(2, ntag.tag_id());

        if (stmt->executeUpdate() == 0) {
            throw std::runtime_error("Error: [cNotaTagDAO] Delete falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

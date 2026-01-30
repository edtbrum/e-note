#include "cNotaLinkDAO.h"
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

cNotaLinkDAO::cNotaLinkDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cNotaLinkDAO::get() {
    return m_conn;
}

void cNotaLinkDAO::insert(cNotaLink& nlink) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO nota_link (tipo, url, nota_origem_id, nota_destino_id) VALUES (?, ?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, nlink.tipo());
        stmt->setString(2, nlink.url());
        stmt->setInt(3, nlink.nota_origem_id());
        stmt->setInt(4, nlink.nota_destino_id());

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: Insert falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

std::vector<cNotaLink> cNotaLinkDAO::findbynotaorigem(int id) {
    std::vector<cNotaLink> nlink;
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT id, tipo, url, nota_destino_id FROM nota_link WHERE nota_origem_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        while (res->next()) {
            cNotaLink nl;
            nl.setidentifier(res->getInt("id"));
            nl.settipo(res->getString("tipo"));
            nl.seturl(res->getString("url"));
            nl.setnota_origem_id(id);
            nl.setnota_destino_id(res->getInt("nota_destino_id"));
            nlink.push_back(nl);
        }

        if (nlink.empty()) {
            throw std::runtime_error("Error: Register not found, nota_origem_id = " + std::to_string(id));
        }

        return nlink;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

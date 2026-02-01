#include "cLembreteDAO.h"
#include "domain/cLembrete.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>

cLembreteDAO::cLembreteDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cLembreteDAO::get() {
    return m_conn;
}

void cLembreteDAO::insert(const cLembrete& lembrete, int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO lembrete (id, data_hora, ativo, nota_id) VALUES (?, ?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, lembrete.identifier());
        stmt->setString(2, lembrete.data_hora());
        stmt->setBoolean(3, lembrete.ativo());
        stmt->setInt(4, notaid);

        int rows = stmt->executeUpdate();
        if (!rows) {
            throw std::runtime_error("Error: [cLembreteDAO] Insert falhou");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

cLembrete cLembreteDAO::findbyid(int id) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT data_hora, ativo, nota_id FROM lembrete WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, id);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cLembrete lembrete;
            lembrete.setidentifier(id);
            lembrete.setdata_hora(res->getString("data_hora"));
            lembrete.setativo(res->getBoolean("ativo"));
            lembrete.setnota_id(res->getInt("nota_id"));
            return lembrete;
        }

        throw std::runtime_error("Error: [lembrete] Register not found by id = " + std::to_string(id));
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

#include "cLembreteDAO.h"
#include "domain/cLembrete.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/sqlstring.h>
#include <memory>
#include <optional>

cLembreteDAO::cLembreteDAO(cConnectionMySQL& conn)
: m_conn(conn) {}

cConnectionMySQL& cLembreteDAO::get() {
    return m_conn;
}

void cLembreteDAO::insert(const cLembrete& lembrete, int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "INSERT INTO lembrete (data_hora, ativo, nota_id) VALUES (?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, lembrete.data_hora());
        stmt->setBoolean(2, lembrete.ativo());
        stmt->setInt(3, notaid);

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

std::optional<cLembrete> cLembreteDAO::findbynotaid(int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "SELECT * FROM lembrete WHERE nota_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, notaid);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            cLembrete lembrete;
            lembrete.setidentifier(res->getInt("id"));
            lembrete.setdata_hora(res->getString("data_hora"));
            lembrete.setativo(res->getBoolean("ativo"));
            lembrete.setnota_id(res->getInt("nota_id"));
            return lembrete;
        }
        else {
            return std::nullopt;
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cLembreteDAO::deletebynotaid(int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "DELETE FROM lembrete WHERE nota_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setInt(1, notaid);

        if (stmt->executeUpdate() == 0) {
            throw std::runtime_error("Error: [cLembreteDAO] Delete falhou, nota id = " + std::to_string(notaid));
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cLembreteDAO::update(const cLembrete& lembrete, int notaid) {
    try {
        auto *conn = m_conn.connection();
        sql::SQLString ssql = "UPDATE lembrete SET data_hora = ?, ativo = ? WHERE nota_id = ?";
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(ssql));
        stmt->setString(1, lembrete.data_hora());
        stmt->setBoolean(2, lembrete.ativo());
        stmt->setInt(3, notaid);
        stmt->executeUpdate();
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

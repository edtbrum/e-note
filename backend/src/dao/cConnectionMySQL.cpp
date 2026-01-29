#include "cConnectionMySQL.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <stdexcept>
#include <string>

cConnectionMySQL::cConnectionMySQL() {
    std::string hostname = "tcp://127.0.0.1:3306";
    std::string username = "dev";
    std::string password = "password";
    std::string schema = "db_enote";

    try {
        sql::Driver *driver = get_driver_instance();
        m_conn.reset(driver->connect(hostname,username,password));
        m_conn->setSchema(schema);
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

cConnectionMySQL::~cConnectionMySQL() {
    m_conn->close();
}

sql::Connection* cConnectionMySQL::connection() noexcept {
    return m_conn ? m_conn.get() : nullptr;
}

bool cConnectionMySQL::isConnected() const {
    try {
        return m_conn && m_conn->isValid();
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

void cConnectionMySQL::reconnect() {
    if (this->isConnected()) { return; }

    try {
        if (m_conn && m_conn->reconnect()) {
            m_conn->setSchema("db_enote");
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Error: " + std::string(e.what()));
    }
}

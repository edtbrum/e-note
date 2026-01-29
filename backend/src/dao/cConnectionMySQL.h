#pragma once

#include <cppconn/connection.h>
#include <memory>

class cConnectionMySQL {
public:
    cConnectionMySQL();
    ~cConnectionMySQL();

    sql::Connection* connection() noexcept;

    bool isConnected() const;
    void reconnect();

private:
    std::unique_ptr<sql::Connection> m_conn;
};

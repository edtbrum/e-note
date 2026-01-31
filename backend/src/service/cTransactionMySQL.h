#pragma once

#include <cppconn/connection.h>

class cTransactionMySQL {
public:
    explicit cTransactionMySQL(sql::Connection* conn)
        : m_conn(conn), m_oldAutoCommit(conn->getAutoCommit()), m_committed(false)
    {
        m_conn->setAutoCommit(false);
    }

    void commit() {
        m_conn->commit();
        m_committed = true;
    }

    ~cTransactionMySQL() {
        if (!m_committed) {
            m_conn->rollback();
        }
        m_conn->setAutoCommit(m_oldAutoCommit);
    }

private:
    sql::Connection* m_conn;
    bool m_oldAutoCommit;
    bool m_committed;
};

#pragma once

#include "dao/INotaLinkDAO.h"
#include "dao/cConnectionMySQL.h"

class cNotaLinkDAO : INotaLinkDAO {
public:
    cNotaLinkDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cNotaLink& nlink) override;
    void insertBatch(const std::vector<cNotaLink>& links, int notaid) override;
    std::vector<cNotaLink> findbynotaorigem(int id) override;

private:
    cConnectionMySQL& m_conn;
};

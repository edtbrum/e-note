#pragma once

#include "dao/INotaTagDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cNotaTag.h"

class cNotaTagDAO : public INotaTagDAO {
public:
    cNotaTagDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cNotaTag& ntag) override;
    std::vector<cNotaTag> findbynotaid (int id) override;

private:
    cConnectionMySQL& m_conn;
};

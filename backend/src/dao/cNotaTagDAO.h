#pragma once

#include "dao/INotaTagDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cNotaTag.h"

class cNotaTagDAO : public INotaTagDAO {
public:
    cNotaTagDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cNotaTag& ntag) override;
    void insertBatch(const std::vector<cNotaTag>& tags, int notaid) override;
    std::vector<cNotaTag> findbynotaid (int id) override;
    void deletebyid(const cNotaTag& ntag) override;

private:
    cConnectionMySQL& m_conn;
};

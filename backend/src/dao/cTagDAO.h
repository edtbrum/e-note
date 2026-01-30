#pragma once

#include "dao/ITagDAO.h"
#include "dao/cConnectionMySQL.h"

class cTagDAO : public ITagDAO {
public:
    cTagDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cTag tag) override;
    cTag findbyid(int id) override;

private:
    cConnectionMySQL& m_conn;
};
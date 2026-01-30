#pragma once

#include "dao/INotaDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cNota.h"

class cNotaDAO : public INotaDAO {
public:
    cNotaDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cNota& nota) override;
    void update(cNota& nota) override;
    cNota findbyid(int id) override;

private:
    cConnectionMySQL& m_conn;
};

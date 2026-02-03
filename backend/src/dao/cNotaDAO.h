#pragma once

#include "dao/INotaDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cNota.h"

class cNotaDAO : public INotaDAO {
public:
    cNotaDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    int insert(const cNota& nota) override;
    void update(cNota& nota) override;
    cNota findbyid(int id) override;
    std::vector<cNota> find() override;
    void deletebyid(int id) override;

private:
    cConnectionMySQL& m_conn;
};

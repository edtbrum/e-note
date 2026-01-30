#pragma once

#include "dao/ILembreteDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"

class cLembreteDAO : public ILembreteDAO {
public:
    cLembreteDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cLembrete& lembrete) override;
    cLembrete findbyid(int id) override;

private:
    cConnectionMySQL& m_conn;
};

#pragma once

#include "dao/ILembreteDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"

class cLembreteDAO : public ILembreteDAO {
public:
    cLembreteDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(const cLembrete& lembrete, int notaid) override;
    cLembrete findbyid(int id) override;
    std::optional<cLembrete> findbynotaid(int notaid) override;
    void deletebynotaid(int notaid) override;
    void update(const cLembrete& lembrete, int notaid) override;

private:
    cConnectionMySQL& m_conn;
};

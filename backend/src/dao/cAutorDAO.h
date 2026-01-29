#pragma once

#include "dao/IAutorDAO.h"
#include "dao/cConnectionMySQL.h"

class cAutorDAO : public IAutorDAO {
public:
    cAutorDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    void insert(cAutor& autor) override;
    void update(cAutor& autor) override;
    cAutor find(cAutor& autor, eSearchAuthor type) override;

private:
    cConnectionMySQL& m_conn;
};
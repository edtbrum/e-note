#pragma once

#include "dao/IAutorDAO.h"
#include "dao/cConnectionMySQL.h"

class cAutorDAO : public IAutorDAO {
public:
    cAutorDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    int insert(const cAutor& autor) override;
    void update(cAutor& autor) override;
    cAutor findbyid(int id) override;
    std::vector<cAutor> list() override;
    void deletebyid(int id) override;

private:
    cConnectionMySQL& m_conn;
};

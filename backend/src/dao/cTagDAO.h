#pragma once

#include "dao/ITagDAO.h"
#include "dao/cConnectionMySQL.h"

class cTagDAO : public ITagDAO {
public:
    cTagDAO(cConnectionMySQL& conn);

    cConnectionMySQL& get() override;
    int insert(const std::string nome) override;
    cTag findbyid(int id) override;
    std::vector<cTag> list() override;
    void deletebyid(int id) override;
    int verifytag(int tag_id) override;

private:
    cConnectionMySQL& m_conn;
};

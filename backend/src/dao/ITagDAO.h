#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cTag.h"
#include <string>
#include <vector>

class ITagDAO {
public:
    virtual ~ITagDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual int insert(const std::string nome) = 0;
    virtual cTag findbyid(int id) = 0;
    virtual std::vector<cTag> list() = 0;
    virtual void deletebyid(int id) = 0;
    virtual int verifytag(int tag_id) = 0;
};

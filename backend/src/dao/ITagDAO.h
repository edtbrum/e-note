#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cTag.h"

class ITagDAO {
public:
    virtual ~ITagDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cTag tag) = 0;
    virtual cTag findbyid(int id) = 0;
};

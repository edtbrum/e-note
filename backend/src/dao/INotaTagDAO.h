#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cNotaTag.h"

class INotaTagDAO {
public:
    virtual ~INotaTagDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cNotaTag& ntag) = 0;
    virtual cNotaTag findbynotaid (int id) = 0;
};
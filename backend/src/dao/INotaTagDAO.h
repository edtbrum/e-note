#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cNotaTag.h"
#include <vector>

class INotaTagDAO {
public:
    virtual ~INotaTagDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cNotaTag& ntag) = 0;
    virtual void insertBatch(const std::vector<cNotaTag>& tags, int notaid) = 0;
    virtual std::vector<cNotaTag> findbynotaid (int id) = 0;
    virtual void deletebyid(const cNotaTag& ntag) = 0;
};

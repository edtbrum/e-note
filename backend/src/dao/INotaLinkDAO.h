#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cNotaLink.h"
#include <vector>

class INotaLinkDAO {
public:
    virtual ~INotaLinkDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cNotaLink& nlink) = 0;
    virtual void insertBatch(const std::vector<cNotaLink>& links, int notaid) = 0;
    virtual std::vector<cNotaLink> findbynotaorigem(int id) = 0;
    virtual void deletebyurl(const cNotaLink& nlink) = 0;
};

#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cAutor.h"
#include <vector>

class IAutorDAO {
public:
    virtual ~IAutorDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual int insert(const cAutor& autor) = 0;
    virtual void update(cAutor& autor) = 0;
    virtual cAutor findbyid(int id) = 0;
    virtual std::vector<cAutor> list() = 0;
};

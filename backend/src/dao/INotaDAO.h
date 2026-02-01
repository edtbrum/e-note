#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cNota.h"

class INotaDAO {
public:
    virtual ~INotaDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual int insert(const cNota& nota) = 0;
    virtual void update(cNota& nota) = 0;
    virtual cNota findbyid(int id) = 0;
};
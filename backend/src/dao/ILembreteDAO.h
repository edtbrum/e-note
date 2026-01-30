#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"

class ILembreteDAO {
public:
    virtual ~ILembreteDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cLembrete& lembrete) = 0;
    virtual cLembrete findbyid(int id) = 0;
};

#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"
#include <optional>

class ILembreteDAO {
public:
    virtual ~ILembreteDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(const cLembrete& lembrete, int notaid) = 0;
    virtual cLembrete findbyid(int id) = 0;
    virtual std::optional<cLembrete> findbynotaid(int notaid) = 0;
};

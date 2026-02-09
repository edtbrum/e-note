#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cNota.h"
#include <string>
#include <vector>

struct sNotaTituloId {
    int id;
    std::string titulo;
};

class INotaDAO {
public:
    virtual ~INotaDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual int insert(const cNota& nota) = 0;
    virtual void update(const cNota& nota) = 0;
    virtual cNota findbyid(int id) = 0;
    virtual std::vector<cNota> find() = 0;
    virtual void deletebyid(int id) = 0;
    virtual int verifynota(int nota_id) = 0;
    virtual std::vector<sNotaTituloId> listtituloid() = 0;
    virtual std::vector<cNota> searchtext(const std::string text) = 0;
};

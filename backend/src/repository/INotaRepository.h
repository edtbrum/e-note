#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include <vector>

class INotaRepository {
public:
    virtual ~INotaRepository() = default;

    virtual int insertNota(cConnectionMySQL& conn, const cNota& nota) = 0;
    virtual void insertLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) = 0;
    virtual void insertTags(cConnectionMySQL& conn, const std::vector<cNotaTag>& tags, int notaid) = 0;
    virtual void insertLinks(cConnectionMySQL& conn, const std::vector<cNotaLink>& links, int notaid) = 0;

    virtual cNota findNotaById(cConnectionMySQL& conn, int notaid) = 0;
    virtual std::optional<cLembrete> findLembreteByNotaid(cConnectionMySQL& conn, int notaid) = 0;
    virtual std::vector<cNotaTag> findTagByNotaid(cConnectionMySQL& conn, int notaid) = 0;
    virtual std::vector<cNotaLink> findLinkByNotaid(cConnectionMySQL& conn, int notaid) = 0;
};

#pragma once

#include "dao/INotaDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include <string>
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

    virtual std::vector<cNota> findNotas(cConnectionMySQL& conn) = 0;

    virtual void updateNota(cConnectionMySQL& conn, const cNota& nota) = 0;
    virtual void updateLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) = 0;
    virtual void deleteLembrete(cConnectionMySQL& conn, int notaid) = 0;
    virtual void deleteTag(cConnectionMySQL& conn, const cNotaTag& notatag) = 0;
    virtual void deleteLink(cConnectionMySQL& conn, const cNotaLink& nlink) = 0;

    virtual std::vector<sNotaTituloId> listNotaByTituloId(cConnectionMySQL& conn) = 0;
    virtual std::vector<cNota> searchNotasByText(cConnectionMySQL& conn, const std::string text) = 0;
};

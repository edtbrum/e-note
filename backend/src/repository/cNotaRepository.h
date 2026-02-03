#pragma once

#include "INotaRepository.h"
#include "domain/cNota.h"

class cNotaRepository : public INotaRepository {
public:
    int insertNota(cConnectionMySQL& conn, const cNota& nota) override;
    void insertLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) override;
    void insertTags(cConnectionMySQL& conn, const std::vector<cNotaTag>& tags, int notaid) override;
    void insertLinks(cConnectionMySQL& conn, const std::vector<cNotaLink>& links, int notaid) override;

    cNota findNotaById(cConnectionMySQL& conn, int notaid) override;
    std::optional<cLembrete> findLembreteByNotaid(cConnectionMySQL& conn, int notaid) override;
    std::vector<cNotaTag> findTagByNotaid(cConnectionMySQL& conn, int notaid) override;
    std::vector<cNotaLink> findLinkByNotaid(cConnectionMySQL& conn, int notaid) override;

    std::vector<cNota> findNotas(cConnectionMySQL& conn) override;
};

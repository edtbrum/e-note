#pragma once

#include "INotaRepository.h"
#include "domain/cNota.h"

class cNotaRepository : public INotaRepository {
public:
    int insertNota(cConnectionMySQL& conn, const cNota& nota) override;
    void insertLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) override;
    void insertTags(cConnectionMySQL& conn, const std::vector<cNotaTag>& tags, int notaid) override;
    void insertLinks(cConnectionMySQL& conn, const std::vector<cNotaLink>& links, int notaid) override;
};

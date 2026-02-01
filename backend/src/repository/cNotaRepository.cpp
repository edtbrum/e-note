#include "cNotaRepository.h"
#include "dao/cLembreteDAO.h"
#include "dao/cNotaDAO.h"
#include "dao/cNotaLinkDAO.h"
#include "dao/cNotaTagDAO.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"

int cNotaRepository::insertNota(cConnectionMySQL& conn, const cNota& nota) {
    cNotaDAO dao(conn);
    return dao.insert(nota);
}

void insertLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) {
    cLembreteDAO dao(conn);
    dao.insert(lembrete, notaid);
}

void insertTags(cConnectionMySQL& conn, const std::vector<cNotaTag>& tags, int notaid) {
    cNotaTagDAO dao(conn);
    dao.insertBatch(tags, notaid);
}

void insertLinks(cConnectionMySQL& conn, const std::vector<cNotaLink>& links, int notaid) {
    cNotaLinkDAO dao(conn);
    dao.insertBatch(links, notaid);
}

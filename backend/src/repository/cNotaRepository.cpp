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

void cNotaRepository::insertLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) {
    cLembreteDAO dao(conn);
    dao.insert(lembrete, notaid);
}

void cNotaRepository::insertTags(cConnectionMySQL& conn, const std::vector<cNotaTag>& tags, int notaid) {
    cNotaTagDAO dao(conn);
    dao.insertBatch(tags, notaid);
}

void cNotaRepository::insertLinks(cConnectionMySQL& conn, const std::vector<cNotaLink>& links, int notaid) {
    cNotaLinkDAO dao(conn);
    dao.insertBatch(links, notaid);
}

cNota cNotaRepository::findNotaById(cConnectionMySQL& conn, int notaid) {
    cNotaDAO dao(conn);
    return dao.findbyid(notaid);
}

std::optional<cLembrete> cNotaRepository::findLembreteByNotaid(cConnectionMySQL& conn, int notaid) {
    cLembreteDAO dao(conn);
    return dao.findbynotaid(notaid);
}

std::vector<cNotaTag> cNotaRepository::findTagByNotaid(cConnectionMySQL& conn, int notaid) {
    cNotaTagDAO dao(conn);
    return dao.findbynotaid(notaid);
}

std::vector<cNotaLink> cNotaRepository::findLinkByNotaid(cConnectionMySQL& conn, int notaid) {
    cNotaLinkDAO dao(conn);
    return dao.findbynotaorigem(notaid);
}

std::vector<cNota> cNotaRepository::findNotas(cConnectionMySQL& conn) {
    cNotaDAO dao(conn);
    return dao.find();
}

void cNotaRepository::updateNota(cConnectionMySQL& conn, const cNota& nota) {
    cNotaDAO dao(conn);
    dao.update(nota);
}

void cNotaRepository::updateLembrete(cConnectionMySQL& conn, const cLembrete& lembrete, int notaid) {
    cLembreteDAO dao(conn);
    dao.update(lembrete, notaid);
}

void cNotaRepository::deleteLembrete(cConnectionMySQL& conn, int notaid) {
    cLembreteDAO dao(conn);
    dao.deletebynotaid(notaid);
}

void cNotaRepository::deleteTag(cConnectionMySQL& conn, const cNotaTag& notatag) {
    cNotaTagDAO dao(conn);
    dao.deletebyid(notatag);
}

void cNotaRepository::deleteLink(cConnectionMySQL& conn, const cNotaLink& nlink) {
    cNotaLinkDAO dao(conn);
    dao.deletebyurl(nlink);
}

#include "cNotaService.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include "service/cTransactionMySQL.h"
#include <optional>
#include <stdexcept>
#include <unordered_set>
#include <vector>

cNotaService::cNotaService(cConnectionMySQL& conn, INotaRepository& repo)
: m_conn(conn), m_repo(repo) {}

int cNotaService::createNota(  
    const cNota& nota, 
    const std::optional<cLembrete>& lembrete,
    const std::vector<cNotaTag>& tags,
    const std::vector<cNotaLink>& links
) {
    auto *conn = m_conn.connection();
    cTransactionMySQL tx(conn);

    int notaid = m_repo.insertNota(m_conn, nota);
    
    if (lembrete.has_value()) {
        m_repo.insertLembrete(m_conn, *lembrete, notaid);
    }
    
    if (!tags.empty()) {
        m_repo.insertTags(m_conn, tags, notaid);
    }
    
    if (!links.empty()) {
        m_repo.insertLinks(m_conn, links, notaid);
    }

    tx.commit();

    return notaid;
}

int cNotaService::createNotaDTO(const CreateNotaDTO& dto) {
    if (dto.titulo.empty() || dto.conteudo.empty()) {
        throw std::runtime_error("Error: Titulo e conteudo obrigatorios");
    }

    cNota nota(dto.titulo,dto.conteudo,dto.autor);

    std::optional<cLembrete> lembrete;
    if (dto.lembreteDataHora.has_value()) {
        cLembrete l;
        l.setativo(true);
        l.setdata_hora(dto.lembreteDataHora.value());
        lembrete = l;
    }

    std::unordered_set<int> seentags;
    std::vector<cNotaTag> tags;
    tags.reserve(dto.tags.size());
    for (const auto& t : dto.tags) {
        if (!seentags.insert(t).second) {
            throw std::runtime_error("Error: Tag duplicada no payload");
        }
        cNotaTag tag;
        tag.settag_id(t);
        tags.push_back(tag);
    }

    std::vector<cNotaLink> links;
    links.reserve(dto.links.size());
    for (const auto& l : dto.links) {
        cNotaLink link;
        link.settipo(l.tipo);
        if (l.tipo == "interno") {
            if (!l.notaDestinoId.has_value()) {
                throw std::runtime_error("Error: Link interno requer notaDestinoId");
            }
            link.setnota_destino_id(l.notaDestinoId.value());
        }
        else if (l.tipo == "externo") {
            if (!l.url.has_value()) {
                throw std::runtime_error("Error: Link externo requer url");
            }
            link.seturl(l.url.value());
        }
        else {
            throw std::runtime_error("Error: Tipo de link invalido");
        }
        links.push_back(link);
    }

    return this->createNota(nota, lembrete, tags, links);
}

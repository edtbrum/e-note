#include "cNotaService.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include "dto/create_nota_dto.h"
#include "dto/nota_response_dto.h"
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

NotaResponseDTO cNotaService::findNotaById(int nota_id) {
    cNota nota = m_repo.findNotaById(m_conn, nota_id);
    std::optional<cLembrete> lembrete = m_repo.findLembreteByNotaid(m_conn, nota_id);
    std::vector<cNotaTag> tags = m_repo.findTagByNotaid(m_conn, nota_id);
    std::vector<cNotaLink> links = m_repo.findLinkByNotaid(m_conn, nota_id);

    NotaResponseDTO dto;
    dto.id = nota.identifier();
    dto.titulo = nota.titulo();
    dto.conteudo = nota.conteudo();
    dto.autor = nota.autor_id();
    dto.criado_em = nota.criado_em();
    dto.atualizado_em = nota.atualizado_em();

    if (lembrete.has_value() && lembrete->ativo()) {
        dto.lembreteDataHora = lembrete->data_hora();
    }

    dto.tags.reserve(tags.size());
    for (const auto& tag : tags) {
        dto.tags.push_back(tag.tag_id());
    }

    dto.links.reserve(links.size());
    for (const auto& l : links) {
        LinkDTO link;
        link.tipo = l.tipo();
        if (link.tipo == "interno") {
            link.notaDestinoId = l.nota_destino_id();
            link.url = std::nullopt;
        }
        else if (link.tipo == "externo") {
            link.notaDestinoId = std::nullopt;
            link.url = l.url();
        }
        else {
            throw std::runtime_error("Error: Tipo de link invalido"); // não pode ocorrer nunca! Banco protege
        }

        dto.links.push_back(link);
    }

    return dto;
}

std::vector<NotaResponseDTO> cNotaService::findNotas() {
    std::vector<cNota> notas = m_repo.findNotas(m_conn);
    std::vector<NotaResponseDTO> listDTO;

    listDTO.reserve(notas.size());
    for (const auto& nota : notas) {
        std::optional<cLembrete> lembrete = m_repo.findLembreteByNotaid(m_conn, nota.identifier());
        std::vector<cNotaTag> tags = m_repo.findTagByNotaid(m_conn, nota.identifier());
        std::vector<cNotaLink> links = m_repo.findLinkByNotaid(m_conn, nota.identifier());

        NotaResponseDTO dto;
        dto.id = nota.identifier();
        dto.titulo = nota.titulo();
        dto.conteudo = nota.conteudo();
        dto.autor = nota.autor_id();
        dto.criado_em = nota.criado_em();
        dto.atualizado_em = nota.atualizado_em();

        if (lembrete.has_value() && lembrete->ativo()) {
            dto.lembreteDataHora = lembrete->data_hora();
        }

        dto.tags.reserve(tags.size());
        for (const auto& tag : tags) {
            dto.tags.push_back(tag.tag_id());
        }

        dto.links.reserve(links.size());
        for (const auto& l : links) {
            LinkDTO link;
            link.tipo = l.tipo();
            if (link.tipo == "interno") {
                link.notaDestinoId = l.nota_destino_id();
                link.url = std::nullopt;
            }
            else if (link.tipo == "externo") {
                link.notaDestinoId = std::nullopt;
                link.url = l.url();
            }
            else {
                throw std::runtime_error("Error: Tipo de link invalido"); // não pode ocorrer nunca! Banco protege
            }

            dto.links.push_back(link);
        }

        listDTO.push_back(dto);
    }

    return listDTO;
}

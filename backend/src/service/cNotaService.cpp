#include "cNotaService.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include "dto/create_nota_dto.h"
#include "dto/nota_response_dto.h"
#include "dto/update_nota_dto.h"
#include "service/cTransactionMySQL.h"
#include "service/makeLinkKey.h"
#include <algorithm>
#include <iterator>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
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

void cNotaService::deleteNota(INotaDAO& notadao, int id) {
    if (notadao.verifynota(id) == 0) {
        notadao.deletebyid(id);
    }
    else {
        throw std::runtime_error("Error: Nota nao pode ser apagada");
    }
}

void cNotaService::updateNotaDTO(const UpdateNotaDTO& dto) {
    auto *conn = m_conn.connection();
    cTransactionMySQL tx(conn);

    // Recupera do banco a nota atual
    NotaResponseDTO old_dto = this->findNotaById(dto.nota_id);

    // Update da tabela nota
    cNota nota;
    nota.setidentifier(dto.nota_id);
    nota.settitulo(dto.titulo);
    nota.setconteudo(dto.conteudo);
    m_repo.updateNota(m_conn, nota);

    // Tabela lembrete: insert/update ou delete ou nada
    cLembrete lembrete;
    switch (dto.lembreteAction) {
        case LembreteAction::NaoAlterar:
        break;

        case LembreteAction::Salvar:
            lembrete.setdata_hora(dto.lembreteDataHora.value());
            lembrete.setativo(dto.ativo.value_or(true));

            if (old_dto.lembreteDataHora.has_value()) {
                m_repo.updateLembrete(m_conn, lembrete, dto.nota_id);
            }
            else {
                m_repo.insertLembrete(m_conn, lembrete, dto.nota_id);
            }
        break;

        case LembreteAction::Remover:
            m_repo.deleteLembrete(m_conn, dto.nota_id);
    }

    // Tabela nota_tag: comparar para inserir ou deletar
    if (dto.tags_flag) {
        std::set<int> atuais(old_dto.tags.begin(), old_dto.tags.end());
        std::set<int> novas(dto.tags.begin(), dto.tags.end());
        std::vector<int> inserir;
        std::vector<int> deletar;
        std::vector<cNotaTag> tags;

        std::set_difference(
            novas.begin(), novas.end(), 
            atuais.begin(), atuais.end(), 
            std::back_inserter(inserir)
        );

        tags.reserve(inserir.size());
        for (auto tagid : inserir) {
            cNotaTag tag(dto.nota_id, tagid);
            tags.push_back(tag);
        }

        if (!tags.empty()) {
            m_repo.insertTags(m_conn, tags, dto.nota_id);
        }

        std::set_difference(
            atuais.begin(), atuais.end(), 
            novas.begin(), novas.end(), 
            std::back_inserter(deletar)
        );

        for (auto tagid : deletar) {
            cNotaTag notatag(dto.nota_id, tagid);
            m_repo.deleteTag(m_conn, notatag);
        }
    }

    // Tabela nota_link: comparar para inserir ou deletar
    if (dto.links_flag) {
        std::unordered_map<std::string, LinkDTO> link_old;
        std::unordered_map<std::string, LinkDTO> link_new;

        for (const auto& l : old_dto.links) {
            link_old[makeLinkKey(l)] = l;
        }

        for (const auto& l : dto.links) {
            link_new[makeLinkKey(l)] = l;
        }

        std::vector<cNotaLink> links;
        for (const auto& [key, link] : link_new) {
            if (!link_old.contains(key)) {
                cNotaLink nlink;
                nlink.settipo(link.tipo);
                if (link.tipo == "interno") {
                    nlink.setnota_destino_id(link.notaDestinoId.value());
                }
                else {
                    nlink.seturl(link.url.value());
                }
                links.push_back(nlink);
            }
        }

        if (!links.empty()) {
            m_repo.insertLinks(m_conn, links, dto.nota_id);
        }

        for (const auto& [key, link] : link_old) {
            if (!link_new.contains(key)) {
                cNotaLink nlink;
                nlink.settipo(link.tipo);
                nlink.setnota_origem_id(dto.nota_id);
                if (link.tipo == "interno") {
                    nlink.setnota_destino_id(link.notaDestinoId.value());
                }
                else {
                    nlink.seturl(link.url.value());
                }
                
                m_repo.deleteLink(m_conn, nlink);
            }
        }
    }

    tx.commit();
}

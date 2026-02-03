#include "nota_parser.h"
#include "util/uTimePoint.h"
#include <crow/json.h>
#include <stdexcept>

CreateNotaDTO parseCreateNota(const crow::json::rvalue& json) {
    CreateNotaDTO dto;

    // campos obrigatórios
    if (!json.has("titulo") || !json.has("conteudo") || !json.has("autor")) {
        throw std::runtime_error("Campos obrigatórios ausentes");
    }

    dto.titulo = json["titulo"].s();
    dto.conteudo = json["conteudo"].s();
    dto.autor = json["autor"].i();

    // lembrete (opcional)
    if (json.has("lembrete") && json["lembrete"].has("data_hora")) {
        dto.lembreteDataHora = json["lembrete"]["data_hora"].s();
    }

    // tags (opcional)
    if (json.has("tags")) {
        for (const auto& t : json["tags"]) {
            dto.tags.push_back(t.i());
        }
    }

    // links (opcional)
    if (json.has("links")) {
        for (const auto& l : json["links"]) {
            LinkDTO link;
            link.tipo = l["tipo"].s();

            if (l.has("nota_destino_id")) {
                link.notaDestinoId = l["nota_destino_id"].i();
            }

            if (l.has("url")) {
                link.url = l["url"].s();
            }

            dto.links.push_back(link);
        }
    }

    return dto;
}

crow::json::wvalue parseFindNota(const NotaResponseDTO& dto) {
    crow::json::wvalue json;

    json["id"] = dto.id;
    json["titulo"] = dto.titulo;
    json["conteudo"] = dto.conteudo;
    json["autor"] = dto.autor;

    json["criado_em"] = to_string(dto.criado_em);

    if (dto.atualizado_em.has_value()) {
        json["atualizado_em"] = to_string(dto.atualizado_em.value());
    }

    if (dto.lembreteDataHora.has_value()) {
        json["lembrete"]["data_hora"] = dto.lembreteDataHora.value();
    }

    if (!dto.tags.empty()) {
        crow::json::wvalue::list datatag;
        for (const auto& tag : dto.tags) {
            datatag.push_back(tag);
        }
        json["tags"] = std::move(datatag);
    }

    if (!dto.links.empty()) {
        crow::json::wvalue::list datalink;
        for (const auto& link : dto.links) {
            crow::json::wvalue jsonLink;
            jsonLink["tipo"] = link.tipo;

            if (link.tipo == "interno") {
                jsonLink["nota_destino_id"] = link.notaDestinoId.value();
            }
            else if (link.tipo == "externo") {
                jsonLink["url"] = link.url.value();
            }
            else {
                throw std::runtime_error("Error: Tipo de link invalido no DTO");
            }

            datalink.push_back(std::move(jsonLink));
        }
        json["links"] = std::move(datalink);
    }

    return json;
}

UpdateNotaDTO parseUpdateNota(const crow::json::rvalue& json) {
    UpdateNotaDTO dto;

    // -------- obrigatórios --------
    if (!json.has("titulo") || !json.has("conteudo")) {
        throw std::runtime_error("Error: Campos obrigatórios ausentes");
    }

    dto.titulo   = json["titulo"].s();
    dto.conteudo = json["conteudo"].s();

    // -------- lembrete --------
    if (!json.has("lembrete")) {
        dto.lembreteAction = LembreteAction::NaoAlterar;
    }
    else if (json["lembrete"].t() == crow::json::type::Null) {
        dto.lembreteAction = LembreteAction::Remover;
    }
    else {
        // veio objeto → salvar (insert ou update)
        const auto& lembrete = json["lembrete"];

        if (!lembrete.has("data_hora")) {
            throw std::runtime_error("Error: lembrete.data_hora é obrigatório");
        }

        dto.lembreteAction   = LembreteAction::Salvar;
        dto.lembreteDataHora = lembrete["data_hora"].s();

        // ativo é opcional
        if (lembrete.has("ativo")) {
            dto.ativo = lembrete["ativo"].b();
        }
    }

    // -------- tags --------
    if (json.has("tags")) {
        if (!(json["tags"].t() == crow::json::type::List)) {
            throw std::runtime_error("Error: tags deve ser uma lista");
        }

        for (const auto& t : json["tags"]) {
            dto.tags.push_back(t.i());
        }

        dto.tags_flag = true;
    }
    else {
        dto.tags_flag = false;
    }

    // -------- links --------
    if (json.has("links")) {
        if (!(json["links"].t() == crow::json::type::List)) {
            throw std::runtime_error("Error: links deve ser uma lista");
        }

        for (const auto& l : json["links"]) {
            LinkDTO link;

            if (!l.has("tipo")) {
                throw std::runtime_error("Error: link.tipo é obrigatório");
            }

            link.tipo = l["tipo"].s();

            if (link.tipo == "interno") {
                if (!l.has("nota_destino_id")) {
                    throw std::runtime_error("Error: link interno exige nota_destino_id");
                }
                link.notaDestinoId = l["nota_destino_id"].i();
            }
            else if (link.tipo == "externo") {
                if (!l.has("url")) {
                    throw std::runtime_error("Error: link externo exige url");
                }
                link.url = l["url"].s();
            }
            else {
                throw std::runtime_error("Error: Tipo de link inválido");
            }

            dto.links.push_back(link);
        }

        dto.links_flag = true;
    }
    else {
        dto.links_flag = false;
    }

    return dto;
}

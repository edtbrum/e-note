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

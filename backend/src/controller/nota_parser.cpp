#include "nota_parser.h"
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

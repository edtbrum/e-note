#pragma once

#include <optional>
#include <string>
#include <vector>

struct LinkDTO {
    std::string tipo; // "interno" | "externo"
    std::optional<int> notaDestinoId;
    std::optional<std::string> url;
};

struct CreateNotaDTO {
    std::string titulo;
    std::string conteudo;

    std::optional<std::string> lembreteDataHora;

    std::vector<int> tags;
    std::vector<LinkDTO> links;
};

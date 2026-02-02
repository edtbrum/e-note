#pragma once

#include "dto/create_nota_dto.h"
#include <string>
#include <vector>
#include <optional>
#include <chrono>

using time_point = std::chrono::system_clock::time_point;

struct NotaResponseDTO {
    int id;
    std::string titulo;
    std::string conteudo;
    int autor;

    time_point criado_em;
    std::optional<time_point> atualizado_em;

    std::optional<std::string> lembreteDataHora;
    std::vector<int> tags;
    std::vector<LinkDTO> links;
};

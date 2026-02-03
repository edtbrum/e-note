#pragma once

#include "dto/create_nota_dto.h"
#include <optional>
#include <string>
#include <vector>

enum class LembreteAction {
    NaoAlterar,
    Salvar,   // insert ou update
    Remover
};


struct UpdateNotaDTO {
    int nota_id;
    std::string titulo;
    std::string conteudo;

    LembreteAction lembreteAction;
    std::optional<std::string> lembreteDataHora;
    std::optional<bool> ativo;

    std::vector<int> tags;
    std::vector<LinkDTO> links;

    bool tags_flag;
    bool links_flag;
};

#pragma once

#include <crow/json.h>
#include "dto/create_nota_dto.h"
#include "dto/nota_response_dto.h"

CreateNotaDTO parseCreateNota(const crow::json::rvalue& json);
crow::json::wvalue parseFindNota(const NotaResponseDTO& dto);

#pragma once

#include <crow/json.h>
#include "dto/create_nota_dto.h"

CreateNotaDTO parseCreateNota(const crow::json::rvalue& json);

#pragma once

#include "dao/cConnectionMySQL.h"
#include "repository/INotaRepository.h"
#include "sCorsMiddleware.h"
#include <crow.h>

void registerCreateNotaRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);
void registerFindNotaByIdRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);
void registerFindNotasRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);

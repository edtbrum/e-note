#pragma once

#include "dao/INotaDAO.h"
#include "dao/cConnectionMySQL.h"
#include "repository/INotaRepository.h"
#include "sCorsMiddleware.h"

void registerCreateNotaRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);
void registerFindNotaByIdRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);
void registerFindNotasRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);
void registerDeleteNotaRoutes(crow::App<CorsMiddleware>& app, INotaDAO& notadao, INotaRepository& repo);
void registerUpdateNoteRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo);

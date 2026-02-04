#pragma once

#include "sCorsMiddleware.h"
#include "dao/IAutorDAO.h"
#include <crow/app.h>

void registerCreateAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao);
void registerUpdateAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao);
void registerDeleteAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao);
void registerListAutoresRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao);

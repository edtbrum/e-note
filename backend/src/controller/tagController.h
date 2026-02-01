#pragma once

#include "sCorsMiddleware.h"
#include "dao/ITagDAO.h"
#include <crow.h>
#include <crow/app.h>

void registerCreateTagRoutes(crow::App<CorsMiddleware>& app, ITagDAO& tagdao);
void registerListTagsRoutes(crow::App<CorsMiddleware>& app, ITagDAO& tagdao);
void registerDeleteTagRoutes(crow::App<CorsMiddleware>& app, ITagDAO& tagdao);

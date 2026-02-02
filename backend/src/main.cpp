#include "cNotaRepository.h"
#include "controller/autorController.h"
#include "controller/sCorsMiddleware.h"
#include "dao/cAutorDAO.h"
#include "dao/cConnectionMySQL.h"
#include "dao/cNotaDAO.h"
#include "dao/cTagDAO.h"
#include "notaController.h"
#include "tagController.h"
#include <crow.h>

int main() {
    crow::App<CorsMiddleware> app;
    cConnectionMySQL conn;
    cAutorDAO autor_dao(conn);
    cTagDAO tag_dao(conn);
    cNotaDAO nota_dao(conn);
    cNotaRepository repo;

    // Author Services
    registerCreateAutorRoutes(app, autor_dao);
    registerUpdateAutorRoutes(app, autor_dao);
    registerDeleteAutorRoutes(app, autor_dao);
    registerListAutoresRoutes(app, autor_dao);

    // Tag Services
    registerCreateTagRoutes(app, tag_dao);
    registerDeleteTagRoutes(app, tag_dao);
    registerListTagsRoutes(app, tag_dao);

    // Nota Services
    registerCreateNotaRoutes(app, conn, repo);

    app.port(18080).multithreaded().run();
    return 0;
}

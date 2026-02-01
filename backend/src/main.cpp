#include "controller/autorController.h"
#include "controller/sCorsMiddleware.h"
#include "dao/cAutorDAO.h"
#include "dao/cConnectionMySQL.h"
#include "dao/cTagDAO.h"
#include "tagController.h"
#include <crow.h>

int main() {
    crow::App<CorsMiddleware> app;
    cConnectionMySQL conn;
    cAutorDAO autor_dao(conn);
    cTagDAO tag_dao(conn);

    // Author Services
    registerCreateAutorRoutes(app, autor_dao);
    registerUpdateAutorRoutes(app, autor_dao);
    registerDeleteAutorRoutes(app, autor_dao);
    registerListAutoresRoutes(app, autor_dao);

    // Tag Services
    registerCreateTagRoutes(app, tag_dao);
    registerDeleteTagRoutes(app, tag_dao);
    registerListTagsRoutes(app, tag_dao);

    app.port(18080).multithreaded().run();
    return 0;
}

#include "controller/autorController.h"
#include "controller/sCorsMiddleware.h"
#include "dao/cAutorDAO.h"
#include "dao/cConnectionMySQL.h"
#include <crow.h>

int main() {
    crow::App<CorsMiddleware> app;
    cConnectionMySQL conn;
    cAutorDAO autor_dao(conn);

    // Author Services
    registerCreateAutorRoutes(app, autor_dao);
    registerUpdateAutorRoutes(app, autor_dao);
    registerDeleteAutorRoutes(app, autor_dao);
    registerListAutoresRoutes(app, autor_dao);

    app.port(18080).multithreaded().run();
    return 0;
}

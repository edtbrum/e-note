#include "notaController.h"
#include "dto/create_nota_dto.h"
#include "nota_parser.h"
#include "service/cNotaService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/json.h>

void registerCreateNotaRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo) {
    CROW_ROUTE(app, "/notes").methods(crow::HTTPMethod::Post)
    ([&conn, &repo](const crow::request& req){
        try {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }
            CreateNotaDTO dto = parseCreateNota(body);
            cNotaService service(conn, repo);

            int nota_id = service.createNotaDTO(dto);

            crow::json::wvalue res;
            res["id"] = nota_id;
            crow::response resp(201, res);
            resp.add_header("Location", "/notes/" + std::to_string(nota_id));
            return resp;
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

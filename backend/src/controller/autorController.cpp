#include "autorController.h"
#include "domain/cAutor.h"
#include "service/cAutorService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <crow/logging.h>
#include <exception>
#include <vector>

void registerCreateAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao) {
    CROW_ROUTE(app, "/authors").methods(crow::HTTPMethod::Post)
    ([&autordao](const crow::request& req){
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("nome") || !body.has("email")) {
                return crow::response(400, "Invalid JSON or missing fields");
            }

            cAutor autor(body["nome"].s(),body["email"].s());
            cAutorService service;
            cAutor retautor = service.createAutor(autordao, autor);

            crow::json::wvalue res;
            res["id"] = retautor.identifier();
            res["nome"] = retautor.nome();
            res["email"] = retautor.email();

            // Para POST que cria recurso, o status correto é 201 Created, não 200.
            // Header Location: /authors/{id}
            crow::response resp(201, res);
            resp.add_header("Location", "/authors/" + std::to_string(retautor.identifier()));
            return resp;
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerUpdateAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao) {
    CROW_ROUTE(app, "/authors/<int>").methods(crow::HTTPMethod::Put)
    ([&autordao](const crow::request& req, int id){
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("nome") || !body.has("email")) {
                return crow::response(400, "Invalid JSON or missing fields");
            }

            cAutor autor(id, body["nome"].s(), body["email"].s());
            cAutorService service;
            service.updateAutor(autordao, autor);

            return crow::response(204); // No Content
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerDeleteAutorRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao) {
    CROW_ROUTE(app, "/authors/<int>").methods(crow::HTTPMethod::Delete)
    ([&autordao](const crow::request& req, int id){
        try {
            if (id < 1) {
                return crow::response(400, "Invalid ID");
            }

            cAutorService service;
            service.deleteAutor(autordao, id);

            return crow::response(204); // No Content
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerListAutoresRoutes(crow::App<CorsMiddleware>& app, IAutorDAO& autordao) {
    CROW_ROUTE(app, "/authors").methods(crow::HTTPMethod::Get)
    ([&autordao](const crow::request& req){
        try {
            cAutorService service;
            std::vector<cAutor> autores = service.listAutores(autordao);

            crow::json::wvalue res;
            crow::json::wvalue::list data;

            for (const auto& autor : autores) {
                crow::json::wvalue item;
                item["id"] = autor.identifier();
                item["nome"] = autor.nome();
                item["email"] = autor.email();
                data.push_back(item);
            }

            res["data"] = std::move(data);
            res["count"] = autores.size();
            return crow::response(200,res);
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

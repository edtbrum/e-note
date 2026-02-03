#include "notaController.h"
#include "dto/create_nota_dto.h"
#include "dto/nota_response_dto.h"
#include "dto/update_nota_dto.h"
#include "nota_parser.h"
#include "service/cNotaService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <vector>

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

void registerFindNotaByIdRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo) {
    CROW_ROUTE(app, "/notes/<int>").methods(crow::HTTPMethod::Get)
    ([&conn, &repo](const crow::request& req, int nota_id){
        try {
            if (nota_id < 1) {
                return crow::response(400, "Invalid ID");
            }

            cNotaService service(conn, repo);
            NotaResponseDTO dto = service.findNotaById(nota_id);
            crow::json::wvalue res = parseFindNota(dto);

            return crow::response (200, res);
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerFindNotasRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo) {
    CROW_ROUTE(app, "/notes").methods(crow::HTTPMethod::Get)
    ([&conn, &repo](const crow::request& req){
        try {
            cNotaService service(conn, repo);
            std::vector<NotaResponseDTO> listDTO = service.findNotas();
            crow::json::wvalue::list listJSON;

            listJSON.reserve(listDTO.size());
            for (const auto& dto : listDTO) {
                crow::json::wvalue item = parseFindNota(dto);
                listJSON.push_back(item);
            }

            crow::json::wvalue res;
            res["data"] = std::move(listJSON);
            res["count"] = listDTO.size();
            return crow::response(200,res);
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerDeleteNotaRoutes(crow::App<CorsMiddleware>& app, INotaDAO& notadao, INotaRepository& repo) {
    CROW_ROUTE(app,"/notes/<int>").methods(crow::HTTPMethod::Delete)
    ([&notadao, &repo](const crow::request& req, int nota_id){
        try {
            if (nota_id < 1) {
                return crow::response(400, "Invalid ID");
            }

            cNotaService service(notadao.get(), repo);
            service.deleteNota(notadao, nota_id);
            return crow::response(204); // No Content
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerUpdateNoteRoutes(crow::App<CorsMiddleware>& app, cConnectionMySQL& conn, INotaRepository& repo) {
    CROW_ROUTE(app, "/notes/<int>").methods(crow::HTTPMethod::Put)
    ([&conn, &repo](const crow::request& req, int nota_id){
        try {
            if (nota_id < 1) {
                return crow::response(400, "Invalid JSON");
            }

            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }

            UpdateNotaDTO dto = parseUpdateNota(body);
            dto.nota_id = nota_id;
            cNotaService service(conn, repo);
            service.updateNotaDTO(dto);
            return crow::response(204); // No Content
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

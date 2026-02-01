#include "tagController.h"
#include "domain/cTag.h"
#include "service/cTagService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_request.h>
#include <crow/json.h>
#include <vector>

void registerCreateTagRoutes(crow::App<CorsMiddleware> &app, ITagDAO &tagdao) {
    CROW_ROUTE(app, "/tags/<string>").methods(crow::HTTPMethod::Post)
    ([&tagdao](const crow::request& req, std::string nome){
        try {
            if (nome.empty()) {
                return crow::response(400, "missing fields");
            }

            cTagService service;
            cTag tag = service.createTag(tagdao, nome);

            crow::json::wvalue res;
            res["id"] = tag.identifier();
            res["nome"] = tag.nome();

            crow::response resp(201, res);
            resp.add_header("Location", "/tags/" + std::to_string(tag.identifier()));
            return resp;
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerListTagsRoutes(crow::App<CorsMiddleware>& app, ITagDAO& tagdao) {
    CROW_ROUTE(app, "/tags").methods(crow::HTTPMethod::Get)
    ([&tagdao](const crow::request& req){
        try {
            cTagService service;
            std::vector<cTag> tags = service.listTags(tagdao);

            crow::json::wvalue::list data;
            for (const auto& tag : tags) {
                crow::json::wvalue item;
                item["id"] = tag.identifier();
                item["nome"] = tag.nome();
                data.push_back(item);
            }

            crow::json::wvalue res;
            res["data"] = std::move(data);
            res["count"] = tags.size();
            return crow::response(200,res);
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

void registerDeleteTagRoutes(crow::App<CorsMiddleware>& app, ITagDAO& tagdao) {
    CROW_ROUTE(app, "/tags/<int>").methods(crow::HTTPMethod::Delete)
    ([&tagdao](const crow::request& req, int id){
        try {
            if (id < 1) {
                return crow::response(400, "Invalid ID");
            }

            cTagService service;
            service.deleteTag(tagdao, id);

            return crow::response(204); // No Content
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << e.what();
            return crow::response(500,"Internal server error");
        }
    });
}

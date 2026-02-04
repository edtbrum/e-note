#pragma once

#define CROW_DISABLE_AUTO_OPTIONS
#include <crow.h>

struct CorsMiddleware {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

        if (req.method == crow::HTTPMethod::Options) {
            res.code = 204;
            res.end();
            return;
        }
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        // garante CORS também na resposta do POST
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }
};

#pragma once
#include <crow.h>

struct CorsMiddleware {
    struct context {};

    void before_handle(crow::request& req,
                       crow::response& res,
                       context&)
    {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");

        // Preflight
        if (req.method == crow::HTTPMethod::OPTIONS) {
            res.code = 204;
            return;
        }
    }

    void after_handle(crow::request&,
                      crow::response& res,
                      context&)
    {
        // GARANTIA FINAL
        if (!res.get_header_value("Access-Control-Allow-Origin").empty())
            return;

        res.add_header("Access-Control-Allow-Origin", "*");
    }
};

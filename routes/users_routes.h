#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <mutex>

#include "../models/User.h"
#include "../utils/validation.h"
#include "../utils/response.h"

extern std::vector<User> users;
extern std::mutex users_mutex;
extern int next_id;

inline void register_user_routes(httplib::Server& app) {

    // CREATE USER
    app.Post("/users", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto body = nlohmann::json::parse(req.body);

            std::string name = body.value("name", "");
            std::string email = body.value("email", "");
            int age = body.value("age", 0);

            if (!is_valid_name(name))
                return json_error(res, 400, "name inválido");
            if (!is_valid_email(email))
                return json_error(res, 400, "email inválido");
            if (!is_valid_age(age))
                return json_error(res, 400, "age inválido");

            std::lock_guard<std::mutex> lock(users_mutex);

            User user{next_id++, name, email, age};
            users.push_back(user);

            nlohmann::json j = user;
            res.status = 201;
            res.set_content(j.dump(), "application/json");

        } catch (...) {
            json_error(res, 400, "JSON inválido");
        }
    });

    // GET ALL USERS
    app.Get("/users", [](const httplib::Request&, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(users_mutex);
        nlohmann::json j = users;
        res.status = 200;
        res.set_content(j.dump(), "application/json");
    });

    // GET USER BY ID
    app.Get(R"(/users/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        int id = std::stoi(req.matches[1]);

        std::lock_guard<std::mutex> lock(users_mutex);
        for (const auto& user : users) {
            if (user.id == id) {
                nlohmann::json j = user;
                res.status = 200;
                res.set_content(j.dump(), "application/json");
                return;
            }
        }
        json_error(res, 404, "usuario no encontrado");
    });

    // DELETE USER
    app.Delete(R"(/users/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        int id = std::stoi(req.matches[1]);

        std::lock_guard<std::mutex> lock(users_mutex);
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->id == id) {
                users.erase(it);
                res.status = 204;
                return;
            }
        }
        json_error(res, 404, "usuario no encontrado");
    });

    // EXTRA ENDPOINT
    app.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.status = 200;
        res.set_content("{\"status\":\"ok\"}", "application/json");
    });
}


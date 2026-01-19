#pragma once
#include "httplib.h"
#include <nlohmann/json.hpp>

inline void json_error(httplib::Response& res, int status, const std::string& message) {
    nlohmann::json j;
    j["error"] = message;
    res.status = status;
    res.set_content(j.dump(), "application/json");
}

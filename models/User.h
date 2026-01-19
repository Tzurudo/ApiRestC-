#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct User {
    int id;
    std::string name;
    std::string email;
    int age;
};

inline void to_json(nlohmann::json& j, const User& u) {
    j = {
        {"id", u.id},
        {"name", u.name},
        {"email", u.email},
        {"age", u.age}
    };
}

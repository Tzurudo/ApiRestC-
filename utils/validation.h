#pragma once
#include <string>

inline bool is_valid_name(const std::string& name) {
    return !name.empty();
}

inline bool is_valid_email(const std::string& email) {
    return email.find('@') != std::string::npos;
}

inline bool is_valid_age(int age) {
    return age > 0;
}

#include "httplib.h"
#include "json.hpp"

#include <iostream>
#include <vector>
#include <mutex>

#include "routes/users_routes.h"

std::vector<User> users;
std::mutex users_mutex;
int next_id = 1;

int main() {
    httplib::Server app;

    register_user_routes(app);

    std::cout << "Servidor corriendo en http://localhost:8080\n";
    app.listen("0.0.0.0", 8080);
}

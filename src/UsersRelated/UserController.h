#pragma once
#include "../../crow_all.h"


class UserController {
    static const std::string USERS_CSV_FILE_PATH;

public:
    static std::vector<crow::json::wvalue> fetchUsers();

    static std::map<int, std::string> fetchUsersMapping();

    static crow::json::wvalue createUser(const std::string& username);
};

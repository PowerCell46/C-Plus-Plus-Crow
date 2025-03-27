#include "UserController.h"
#include "../Common/Constants.h"


const std::string UserController::USERS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\users.csv";


crow::json::wvalue UserController::createUser(const std::string &username) {
    const auto users = UserController::fetchUsers();
    const size_t userId = users.size() + 1;

    std::ofstream fileStream{USERS_CSV_FILE_PATH, std::ios::app};

    fileStream << (userId > 1 ? "\n" : "") << userId << CSV_DELIMITER << username;

    crow::json::wvalue entry;
    entry["userId"] = userId;
    entry["username"] = username;

    return entry;
}


std::vector<crow::json::wvalue> UserController::fetchUsers() {
    std::vector<crow::json::wvalue> users;
    users.reserve(10);

    std::ifstream fileStream{USERS_CSV_FILE_PATH};
    std::string currentLine;

    while (std::getline(fileStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string currentValue;
        std::getline(currentLineStream, currentValue, CSV_DELIMITER);

        crow::json::wvalue entry;
        entry["userId"] = std::stoi(currentValue);

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["username"] = currentValue;

        users.push_back(entry);
    }

    return users;
}


std::map<int, std::string> UserController::fetchUsersMapping() {
    std::map<int, std::string> result;

    const std::vector<crow::json::wvalue> users = UserController::fetchUsers();

    for (const crow::json::wvalue& user : users) {
        int userId = std::stoi(user["userId"].dump());
        std::string name = user["username"].dump();
        result.insert({userId, std::string(name.begin() + 1, name.end() - 1)});
    }

    return result;
}

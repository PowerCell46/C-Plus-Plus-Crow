#include "UserController.h"
#include "../Common/Constants.h"


const std::string UserController::USERS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\users.csv";


crow::json::wvalue UserController::createUser(const std::string &username) {
    const auto users = UserController::fetchUsers();
    const size_t userId = users.size() + 1;

    std::ofstream fileStream{USERS_CSV_FILE_PATH, std::ios::app};

    fileStream << (userId > 1 ? "\n" : "") << userId << CSV_DELIMITER << username;

    crow::json::wvalue entry;
    entry["id"] = userId;
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
        entry["id"] = std::stoi(currentValue);

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["username"] = currentValue;

        users.push_back(entry);
    }

    return users;
}

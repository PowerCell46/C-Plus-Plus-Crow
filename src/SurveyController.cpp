//
// Created by HP ZBook 17 G5 on 24.3.2025 г..
//

#include "SurveyController.h"


crow::response SurveyController::submitQuestion(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::response(400);

    const int userId = requestBody["userId"].i();
    const int questionId = requestBody["questionId"].i();
    const std::string content = requestBody["content"].s();

    std::ostringstream stringStream;
    stringStream << "User id: " << userId << ", Question id: " << questionId << "\nContent: " << content <<
            '\n';

    std::ofstream fileStream{"C:\\Programming\\C++\\C++ProjectCLion\\file.txt", std::ios::app};
    fileStream << stringStream.str();

    return crow::response{stringStream.str()};
}

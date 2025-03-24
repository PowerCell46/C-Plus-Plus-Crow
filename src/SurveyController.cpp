#include "SurveyController.h"


crow::json::wvalue SurveyController::createQuestion(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const int questionId = requestBody["questionId"].i();
    const std::string content = requestBody["content"].s();

    std::ofstream fileStream{"C:\\Programming\\C++\\C++ProjectCLion\\questions.csv", std::ios::app};
    fileStream << '\n' << questionId << ',' << content;

    crow::json::wvalue entry;
    entry["id"] = questionId;
    entry["question"] = content;

    return entry;
}


crow::json::wvalue SurveyController::getQuestions() {
    crow::json::wvalue response(fetchQuestions());

    return response;
}


crow::json::wvalue SurveyController::getSingleQuestion(const int &questionId) {
    const auto questions = fetchQuestions();

    for (const crow::json::wvalue& question : questions)
        if (question["id"].dump() == std::to_string(questionId))
            return question;

    return crow::json::wvalue();
}


std::vector<crow::json::wvalue> SurveyController::fetchQuestions() {
    std::vector<crow::json::wvalue> questions;

    std::ifstream fileStream{"C:\\Programming\\C++\\C++ProjectCLion\\questions.csv"};
    std::string currentLine;

    while (std::getline(fileStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string idStr, question;
        std::getline(currentLineStream, idStr, ',');
        std::getline(currentLineStream, question, ',');
        int id = std::stoi(idStr);

        crow::json::wvalue entry;
        entry["id"] = id;
        entry["question"] = question;
        questions.push_back(entry);
    }

    return questions;
}


// crow::json::wvalue SurveyController::alterQuestion(const crow::request &req) {
//     const auto requestBody = crow::json::load(req.body);
//     if (!requestBody)
//         return crow::json::wvalue();
//
//     const int questionId = requestBody["questionId"].i();
//     const std::string content = requestBody["content"].s();
//
//     return;
// }

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


crow::json::wvalue SurveyController::getQuestions() {
    std::ifstream fileStream{"C:\\Programming\\C++\\C++ProjectCLion\\questions.csv"};
    std::string currentLine;

    while (std::getline(fileStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string idStr, question;
        std::getline(currentLineStream, idStr, ',');
        std::getline(currentLineStream, question, ',');
        int id = std::stoi(idStr);
        std::cout << id << ' ' << question << '\n';
    }

    crow::json::wvalue response({
        {"first", "Hello world!"}, /* stores a char const* hence a json::type::String */
        {"second", std::string("How are you today?")}, /* stores a std::string hence a json::type::String. */
        {"third", 54}, /* stores an int (as 54 is an int literal) hence a std::int64_t. */
        {"fourth", (int64_t) 54l}, /* stores a long (as 54l is a long literal) hence a std::int64_t. */
        {"fifth", 54u}, /* stores an unsigned int (as 54u is a unsigned int literal) hence a std::uint64_t. */
        {"sixth", (uint64_t) 54ul},
        /* stores an unsigned long (as 54ul is an unsigned long literal) hence a std::uint64_t. */
        {"seventh", 2.f}, /* stores a float (as 2.f is a float literal) hence a double. */
        {"eighth", 2.}, /* stores a double (as 2. is a double literal) hence a double. */
        {"ninth", nullptr}, /* stores a std::nullptr hence json::type::Null . */
        {"tenth", true} /* stores a bool hence json::type::True . */
    });

    return response;
}

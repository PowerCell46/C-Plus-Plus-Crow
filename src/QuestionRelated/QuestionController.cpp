#include "QuestionController.h"
#include "../Common/Constants.h"


const std::string QuestionController::QUESTIONS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\questions.csv";


crow::json::wvalue QuestionController::createQuestion(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const int questionId = requestBody["questionId"].i();
    const std::string content = requestBody["content"].s();

    std::ofstream fileStream{QUESTIONS_CSV_FILE_PATH, std::ios::app};
    fileStream << '\n' << questionId << CSV_DELIMITER << content;

    crow::json::wvalue entry;
    entry["questionId"] = questionId;
    entry["question"] = content;

    return entry;
}


crow::json::wvalue QuestionController::getQuestions() {
    crow::json::wvalue response(fetchQuestions());

    return response;
}


crow::json::wvalue QuestionController::getSingleQuestion(const int &questionId) {
    const std::string questionIdStr = std::to_string(questionId);

    const auto questions = fetchQuestions();

    for (const crow::json::wvalue &question: questions)
        if (question["questionId"].dump() == questionIdStr)
            return question;

    return crow::json::wvalue();
}


std::vector<crow::json::wvalue> QuestionController::fetchQuestions() {
    std::vector<crow::json::wvalue> questions;
    questions.reserve(10);

    std::ifstream fileStream{QUESTIONS_CSV_FILE_PATH};
    std::string currentLine;

    while (std::getline(fileStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};

        std::string questionIdStr, question;
        std::getline(currentLineStream, questionIdStr, CSV_DELIMITER);
        std::getline(currentLineStream, question, CSV_DELIMITER);

        int questionId = std::stoi(questionIdStr);

        crow::json::wvalue entry;
        entry["questionId"] = questionId;
        entry["question"] = question;
        questions.push_back(entry);
    }

    return questions;
}


std::map<int, std::string> QuestionController::fetchQuestionsMapping() {
    std::map<int, std::string> result;

    const std::vector<crow::json::wvalue> questions = QuestionController::fetchQuestions();

    for (const crow::json::wvalue& question : questions) {
        int questionId = std::stoi(question["questionId"].dump());
        std::string questionContent = question["question"].dump();
        result.insert({questionId, std::string(questionContent.begin() + 1, questionContent.end() - 1)});
    }

    return result;
}


crow::json::wvalue QuestionController::alterQuestion(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const int questionId = requestBody["questionId"].i();
    const std::string newContent = requestBody["newContent"].s();

    std::stringstream fileBufferStream{};
    std::ifstream fileReadStream{QUESTIONS_CSV_FILE_PATH};

    std::string currentLine;
    while (std::getline(fileReadStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string currentIdStr;
        std::getline(currentLineStream, currentIdStr, CSV_DELIMITER);

        if (const int currentId = std::stoi(currentIdStr); currentId == questionId)
            fileBufferStream << currentId << CSV_DELIMITER << newContent << '\n';
        else
            fileBufferStream << currentLine << '\n';
    }

    std::ofstream fileWriteStream{QUESTIONS_CSV_FILE_PATH};
    fileWriteStream << fileBufferStream.str();

    crow::json::wvalue entry;
    entry["questionId"] = questionId;
    entry["newContent"] = newContent;

    return entry;
}


crow::json::wvalue QuestionController::deleteQuestion(const int &questionId) {
    std::stringstream fileBufferStream{};
    std::ifstream fileReadStream{QUESTIONS_CSV_FILE_PATH};

    std::string currentLine;
    while (std::getline(fileReadStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string currentIdStr;
        std::getline(currentLineStream, currentIdStr, CSV_DELIMITER);

        if (const int currentId = std::stoi(currentIdStr); currentId != questionId)
            fileBufferStream << currentLine << '\n';
    }

    std::ofstream fileWriteStream{QUESTIONS_CSV_FILE_PATH};
    fileWriteStream << fileBufferStream.str();

    crow::json::wvalue entry;
    entry["questionId"] = questionId;

    return entry;
}
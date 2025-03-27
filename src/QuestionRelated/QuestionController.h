#pragma once
#include "../../crow_all.h"


class QuestionController {
    static const std::string QUESTIONS_CSV_FILE_PATH;

public:
    static crow::json::wvalue createQuestion(const crow::request &req);

    static crow::json::wvalue getQuestions();

    static crow::json::wvalue getSingleQuestion(const int &questionId);

    static crow::json::wvalue alterQuestion(const crow::request &req);

    static crow::json::wvalue deleteQuestion(const int &questionId);

    static std::vector<crow::json::wvalue> fetchQuestions();

    static std::map<int, std::string> fetchQuestionsMapping();
};

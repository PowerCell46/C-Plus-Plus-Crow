#pragma once
#include "../crow_all.h"


class SurveyController {
    static std::vector<crow::json::wvalue> fetchQuestions();

public:
    static crow::json::wvalue createQuestion(const crow::request &req);

    static crow::json::wvalue getQuestions();

    static crow::json::wvalue getSingleQuestion(const int &questionId);

    static crow::json::wvalue alterQuestion(const crow::request &req);
};

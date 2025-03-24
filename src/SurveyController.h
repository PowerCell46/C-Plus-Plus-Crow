#pragma once
#include "../crow_all.h"


class SurveyController {
public:
    static crow::response submitQuestion(const crow::request &req);

    static crow::json::wvalue getQuestions();
};

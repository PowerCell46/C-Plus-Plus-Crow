#ifndef SURVEYCONTROLLER_H
#define SURVEYCONTROLLER_H
#include "../crow_all.h"


class SurveyController {
public:
    static crow::response submitQuestion(const crow::request &req);
};


#endif
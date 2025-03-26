#pragma once
#include "../../crow_all.h"


class SubmissionController {
    static const std::string SUBMISSIONS_CSV_FILE_PATH;

    static std::vector<std::vector<std::string>> fetchSubmissions();

public:
    static crow::json::wvalue submitSurvey(const crow::request &req);
};

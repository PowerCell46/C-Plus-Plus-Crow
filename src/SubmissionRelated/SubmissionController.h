#pragma once
#include "../../crow_all.h"


class SubmissionController {
    static const std::string SUBMISSIONS_CSV_FILE_PATH;

    static std::vector<crow::json::wvalue> fetchSubmissions();

public:
    static crow::json::wvalue submitSurvey(const crow::request &req);

    static crow::json::wvalue getSubmissions();

    static crow::json::wvalue getSingleSubmission(const int &submissionId);

    static crow::json::wvalue alterSubmission(const crow::request &req);

    static crow::json::wvalue deleteSubmission(const int &submissionId);
};
#pragma once
#include "../../crow_all.h"


class SubmissionController {
    static const std::string SUBMISSIONS_CSV_FILE_PATH;

    static std::vector<crow::json::wvalue> fetchSubmissions();

public:
    static crow::json::wvalue submitSurvey(const crow::request &req);

    static crow::json::wvalue getSubmissions();

    // static crow::json::wvalue getSingleSubmission(const int &questionId);

    // Edit submission

    // Delete submission
};


// ___________________________________
// | user_id| questionId | answer    |
// |_________________________________|
// | 1      | 1          | my answer |
// | 1      | 1          | my answer |
// | 1      | 1          | my answer |
// | 1      | 1          | my answer |
// | 1      | 1          | my answer |
// |_________________________________|

// _________________
// | id| username  |
// |_______________|
// | 1 | PowerCell |
// | 1 | PowerCell |
// | 1 | PowerCell |
// | 1 | PowerCell |
// |_______________|
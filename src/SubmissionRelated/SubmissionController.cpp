#include "SubmissionController.h"
#include "../QuestionRelated/QuestionController.h"


const std::string SubmissionController::SUBMISSIONS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\submissions.csv";


crow::json::wvalue SubmissionController::submitSurvey(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const std::string username = requestBody["username"].s();
    auto submissionsArray = requestBody["submissions"];

    std::ofstream fileStream{SUBMISSIONS_CSV_FILE_PATH, std::ios::app};
    fileStream << '\n' << username << ',';

    for (size_t i = 0; i < submissionsArray.size() - 1; ++i)
        fileStream << submissionsArray[i]["answer"].s() << ',';
    fileStream << submissionsArray[submissionsArray.size() - 1]["answer"].s();

    crow::json::wvalue entry;
    //TODO: submissionId
    // entry["submissionId"] = submissionId;
    entry["username"] = username;

    return entry;
}

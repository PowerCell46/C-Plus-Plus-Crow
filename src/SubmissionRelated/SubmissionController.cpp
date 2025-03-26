#include "SubmissionController.h"
#include "../QuestionRelated/QuestionController.h"
#include "../Common/Constants.h"


const std::string SubmissionController::SUBMISSIONS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\submissions.csv";


crow::json::wvalue SubmissionController::submitSurvey(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    auto submissions = SubmissionController::fetchSubmissions();
    const size_t submissionId = submissions.size() + 1;

    const std::string username = requestBody["username"].s();
    auto submissionsArray = requestBody["submissions"];

    std::ofstream fileStream{SUBMISSIONS_CSV_FILE_PATH, std::ios::app};
    fileStream << (submissionId > 1 ? "\n" : "") << submissionId << CSV_DELIMITER << username << CSV_DELIMITER;

    for (size_t i = 0; i < submissionsArray.size() - 1; ++i)
        fileStream << submissionsArray[i]["answer"].s() << CSV_DELIMITER;
    fileStream << submissionsArray[submissionsArray.size() - 1]["answer"].s();

    crow::json::wvalue entry;
    entry["submissionId"] = submissionId;
    entry["username"] = username;

    return entry;
}


std::vector<std::vector<std::string>> SubmissionController::fetchSubmissions() {
    std::vector<std::vector<std::string>> submissions;
    submissions.reserve(15);

    std::ifstream fileStream{SUBMISSIONS_CSV_FILE_PATH};
    std::string currentLine;

    while (fileStream >> currentLine) {
        std::vector<std::string> currentSubmissionValues;

        std::stringstream currentLineStream{currentLine};
        std::string currentValue;
        while (std::getline(currentLineStream, currentValue, CSV_DELIMITER))
            currentSubmissionValues.push_back(currentValue);

        submissions.push_back(currentSubmissionValues);
    }

    return submissions;
}

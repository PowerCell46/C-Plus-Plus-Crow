#include "SubmissionController.h"
#include "../QuestionRelated/QuestionController.h"
#include "../UsersRelated/UserController.h"
#include "../Common/Constants.h"


const std::string SubmissionController::SUBMISSIONS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\submissions.csv";


crow::json::wvalue SubmissionController::submitSurvey(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const auto submissions = SubmissionController::fetchSubmissions();
    size_t currentSubmissionId = submissions.size() + 1;

    crow::json::wvalue users = UserController::createUser(requestBody["username"].s());
    int userId = std::stoi(users["id"].dump());

    const auto submissionsArray = requestBody["submissions"];

    std::ofstream fileStream{SUBMISSIONS_CSV_FILE_PATH, std::ios::app};

    for (size_t i = 0; i < submissionsArray.size(); ++i)
        fileStream <<
                (currentSubmissionId > 1 ? "\n" : "") << (currentSubmissionId++) << CSV_DELIMITER <<
                userId << CSV_DELIMITER << submissionsArray[i]["questionId"].i() << CSV_DELIMITER <<
                submissionsArray[i]["answer"].s();


    // TODO: Change the return type
    crow::json::wvalue entry;
    // entry["submissionId"] = submissionId;
    entry["username"] = requestBody["username"].s();

    return entry;
}


std::vector<crow::json::wvalue> SubmissionController::fetchSubmissions() {
    std::vector<crow::json::wvalue> submissions;
    submissions.reserve(15);

    std::ifstream fileStream{SUBMISSIONS_CSV_FILE_PATH};
    std::string currentLine;

    while (fileStream >> currentLine) {
        std::vector<std::string> currentSubmissionValues;

        std::stringstream currentLineStream{currentLine};
        std::string currentValue;

        crow::json::wvalue entry;

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["id"] = std::stoi(currentValue);

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["userId"] = std::stoi(currentValue);

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["questionId"] = std::stoi(currentValue);

        std::getline(currentLineStream, currentValue, CSV_DELIMITER);
        entry["answer"] = currentValue;

        submissions.push_back(entry);
    }

    return submissions;
}


crow::json::wvalue SubmissionController::getSubmissions() {
    crow::json::wvalue response(fetchSubmissions());

    return response;}


crow::json::wvalue SubmissionController::getSingleSubmission(const int &id) {
    const auto submissions = SubmissionController::fetchSubmissions();

    for (const crow::json::wvalue& submission : submissions)
        if (submission["id"].dump() == std::to_string(id))
            return submission;

    return crow::json::wvalue();
}

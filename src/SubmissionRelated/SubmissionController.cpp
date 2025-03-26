#include "SubmissionController.h"
#include "../QuestionRelated/QuestionController.h"
#include "../UsersRelated/UserController.h"
#include "../Common/Constants.h"


const std::string SubmissionController::SUBMISSIONS_CSV_FILE_PATH = "C:\\Programming\\C++\\C++ProjectCLion\\data\\submissions.csv";


crow::json::wvalue SubmissionController::submitSurvey(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    // TODO: Refactor the fetchSubmissions
    // const auto submissions = SubmissionController::fetchSubmissions();
    // size_t currentSubmissionId = submissions.size() + 1;
    size_t currentSubmissionId = 3 + 1; // TODO: ATM THIS IS HARDCODED

    size_t userId{};
    UserController::createUser(requestBody["username"].s(), userId);

    const auto submissionsArray = requestBody["submissions"];

    std::ofstream fileStream{SUBMISSIONS_CSV_FILE_PATH, std::ios::app};

    for (size_t i = 0; i < submissionsArray.size(); ++i)
        fileStream <<
                (currentSubmissionId > 1 ? "\n" : "") << (currentSubmissionId++) << CSV_DELIMITER <<
                userId << CSV_DELIMITER << submissionsArray[i]["questionId"].i() << CSV_DELIMITER <<
                submissionsArray[i]["answer"].s();

    crow::json::wvalue entry;
    // entry["submissionId"] = submissionId;
    entry["username"] = requestBody["username"].s();

    return entry;
}

// TODO: Change the return type and just count the occurrences
std::vector<std::vector<std::string> > SubmissionController::fetchSubmissions() {
    std::vector<std::vector<std::string> > submissions;
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


// crow::json::wvalue SubmissionController::getSingleSubmission(const int &questionId) {
//     std::vector<crow::json::wvalue> questions;
//
//     std::ifstream fileStream{SUBMISSIONS_CSV_FILE_PATH};
//     std::string currentLine;
//
//     while (std::getline(fileStream, currentLine)) {
//         std::stringstream currentLineStream{currentLine};
//         std::string currentValue;
//         int position{};
//
//         crow::json::wvalue entry;
//
//         while (std::getline(currentLineStream, currentValue, CSV_DELIMITER)) {
//             switch (position) {
//                 case 0:
//                     entry["id"] = currentValue;
//                     break;
//                 case 1:
//                     entry["username"] = currentValue;
//                     break;
//                 default:
//                     entry["question"]
//
//             }
//             ++position;
//         }
//     }
// }

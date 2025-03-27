#include "SubmissionController.h"
#include "../QuestionRelated/QuestionController.h"
#include "../UsersRelated/UserController.h"
#include "../Common/Constants.h"


const std::string SubmissionController::SUBMISSIONS_CSV_FILE_PATH =
        "C:\\Programming\\C++\\C++ProjectCLion\\data\\submissions.csv";


crow::json::wvalue SubmissionController::submitSurvey(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const auto submissions = SubmissionController::fetchSubmissions();
    size_t currentSubmissionId = submissions.size() + 1;

    crow::json::wvalue users = UserController::createUser(requestBody["username"].s());
    int userId = std::stoi(users["userId"].dump());

    std::ofstream fileStream{SUBMISSIONS_CSV_FILE_PATH, std::ios::app};

    const auto submissionsArray = requestBody["submissions"];
    for (size_t i = 0; i < submissionsArray.size(); ++i)
        fileStream << (currentSubmissionId > 1 ? "\n" : "") << (currentSubmissionId++) <<
                CSV_DELIMITER << userId << CSV_DELIMITER << submissionsArray[i]["questionId"].i() <<
                CSV_DELIMITER << submissionsArray[i]["answer"].s();


    // TODO: Change the return type!
    crow::json::wvalue entry;
    entry["userId"] = userId;
    // {}

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
        entry["submissionId"] = std::stoi(currentValue);

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
    std::map<int, std::string> questionsMapping = QuestionController::fetchQuestionsMapping();
    std::map<int, std::string> usersMapping = UserController::fetchUsersMapping();

    std::vector<crow::json::wvalue> submissions = fetchSubmissions();

    for (crow::json::wvalue& submission : submissions) {
        submission["username"] = usersMapping[std::stoi(submission["userId"].dump())];
        submission["question"] = questionsMapping[std::stoi(submission["questionId"].dump())];
    }

    return submissions;
}


crow::json::wvalue SubmissionController::getSingleSubmission(const int &submissionId) {
    const std::string submissionIdStr = std::to_string(submissionId);

    std::map<int, std::string> questionsMapping = QuestionController::fetchQuestionsMapping();
    std::map<int, std::string> usersMapping = UserController::fetchUsersMapping();

    std::vector<crow::json::wvalue> submissions = fetchSubmissions();

    for (crow::json::wvalue& submission : submissions) {
        if (submission["submissionId"].dump() == submissionIdStr) {
            submission["username"] = usersMapping[std::stoi(submission["userId"].dump())];
            submission["question"] = questionsMapping[std::stoi(submission["questionId"].dump())];
            return submission;
        }
    }

    return crow::json::wvalue();
}


crow::json::wvalue SubmissionController::alterSubmission(const crow::request &req) {
    const auto requestBody = crow::json::load(req.body);
    if (!requestBody)
        return crow::json::wvalue();

    const int submissionId = requestBody["submissionId"].i();
    const std::string newAnswer = requestBody["newAnswer"].s();
    std::string userId, questionId;

    std::ifstream fileStream{SUBMISSIONS_CSV_FILE_PATH};
    std::stringstream fileBufferStream{};
    std::string currentLine;

    while (std::getline(fileStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};

        std::string currentIdStr;
        std::getline(currentLineStream, currentIdStr, CSV_DELIMITER);

        if (currentIdStr == std::to_string(submissionId)) {
            std::getline(currentLineStream, userId, CSV_DELIMITER);
            std::getline(currentLineStream, questionId, CSV_DELIMITER);

            fileBufferStream << currentIdStr << CSV_DELIMITER <<
                    userId << CSV_DELIMITER << questionId <<
                    CSV_DELIMITER << newAnswer << '\n';

        } else
            fileBufferStream << currentLine << '\n';
    }

    std::ofstream fileWriteStream{SUBMISSIONS_CSV_FILE_PATH};
    fileWriteStream << fileBufferStream.str();

    crow::json::wvalue entry;
    entry["submissionId"] = submissionId;
    entry["userId"] = userId;
    entry["questionId"] = questionId;
    entry["newAnswer"] = newAnswer;

    return entry;
}


crow::json::wvalue SubmissionController::deleteSubmission(const int &submissionId) {
    const std::string submissionIdStr = std::to_string(submissionId);

    std::stringstream fileBufferStream{};
    std::ifstream fileReadStream{SUBMISSIONS_CSV_FILE_PATH};
    std::string currentLine;

    while (std::getline(fileReadStream, currentLine)) {
        std::stringstream currentLineStream{currentLine};
        std::string currentIdStr;
        std::getline(currentLineStream, currentIdStr, CSV_DELIMITER);

        if (currentIdStr != submissionIdStr)
            fileBufferStream << currentLine << '\n';
    }

    std::ofstream fileWriteStream{SUBMISSIONS_CSV_FILE_PATH};
    fileWriteStream << fileBufferStream.str();

    crow::json::wvalue entry;
    entry["submissionId"] = submissionId;

    return entry;
}

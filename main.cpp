#include "crow_all.h"
#include "./src/QuestionRelated/QuestionController.h"
#include "./src/SubmissionRelated/SubmissionController.h"
#include "./src/Common/Constants.h"


#define GET_ALL_QUESTIONS "/questions/get-all"
#define GET_SINGLE_QUESTION "/questions/<int>"
#define POST_QUESTIONS_SUBMIT "/questions/submit"
#define PATCH_QUESTION "/questions/edit"
#define DELETE_QUESTION "/questions/delete/<int>"
//-----------------------------------------------
#define POST_SURVEY_SUBMIT "/survey/submit"
#define GET_SINGLE_SUBMISSION "/survey/submissions/<int>"
#define GET_ALL_SUBMISSIONS "/survey/submissions/get-all"
#define PATCH_SUBMISSION "/survey/submissions/edit"


class ExampleLogHandler : public crow::ILogHandler {
public:
    void log(std::string /*message*/, crow::LogLevel /*level*/) override {
        //            cerr << "ExampleLogHandler -> " << message;
    }
};


int main() {
    crow::SimpleApp app;

    // GET REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, GET_ALL_QUESTIONS)(QuestionController::getQuestions);


    CROW_ROUTE(app, GET_SINGLE_QUESTION)(QuestionController::getSingleQuestion);


    CROW_ROUTE(app, GET_ALL_SUBMISSIONS)(SubmissionController::getSubmissions);


    CROW_ROUTE(app, GET_SINGLE_SUBMISSION)(SubmissionController::getSingleSubmission);


    // POST REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, POST_QUESTIONS_SUBMIT).methods("POST"_method)(QuestionController::createQuestion);


    CROW_ROUTE(app, POST_SURVEY_SUBMIT).methods("POST"_method)(SubmissionController::submitSurvey);


    // PATCH REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, PATCH_QUESTION).methods("PATCH"_method)(QuestionController::alterQuestion);


    CROW_ROUTE(app, PATCH_SUBMISSION).methods("PATCH"_method)(SubmissionController::alterSubmission);


    // DELETE REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, DELETE_QUESTION).methods("DELETE"_method)(QuestionController::deleteQuestion);


    // -----------------------------------------------------------------------------------------------------------------
    // Ignore all log
    crow::logger::setLogLevel(crow::LogLevel::Debug);
    //crow::logger::setHandler(std::make_shared<ExampleLogHandler>());

    app.port(SERVER_PORT).server_name(SERVER_NAME).multithreaded().run();
}

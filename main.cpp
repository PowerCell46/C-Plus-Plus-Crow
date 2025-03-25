#include "crow_all.h"
#include "./src/SurveyController.h"


#define GET_ALL_QUESTIONS "/questions/get-all"
#define GET_SINGLE_QUESTION "/questions/<int>"
#define POST_SURVEY_SUBMIT "/survey/submit"
#define PATCH_SURVEY_ALTER "/questions/edit"


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

    CROW_ROUTE(app, GET_ALL_QUESTIONS)(SurveyController::getQuestions);


    CROW_ROUTE(app, GET_SINGLE_QUESTION)(SurveyController::getSingleQuestion);


    // POST REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, POST_SURVEY_SUBMIT).methods("POST"_method)(SurveyController::createQuestion);


    // PATCH REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, PATCH_SURVEY_ALTER)
            .methods("PATCH"_method)
            (SurveyController::alterQuestion);


    // DELETE REQUESTS
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, "/item/<int>")
            .methods("DELETE"_method)
            ([](int submissionId) {

                CROW_LOG_INFO << "Submission Id to delete: " << submissionId;

                return crow::response(200, "Submission deleted successfully.");
            });


    // -----------------------------------------------------------------------------------------------------------------
    // ignore all log
    crow::logger::setLogLevel(crow::LogLevel::Debug);
    //crow::logger::setHandler(std::make_shared<ExampleLogHandler>());

    app.port(18080).server_name("CrowCpp").multithreaded().run();
}

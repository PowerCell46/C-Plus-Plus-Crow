#include "crow_all.h"
#include "./src/SurveyController.h"


class ExampleLogHandler : public crow::ILogHandler {
public:
    void log(std::string /*message*/, crow::LogLevel /*level*/) override {
        //            cerr << "ExampleLogHandler -> " << message;
    }
};


int main() {
    crow::SimpleApp app;

    // GET REQUEST
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, "/json")
    ([] {
        crow::json::wvalue x({{"message", "Hello, World!"}});
        x["message2"] = "Hello, World.. Again!";
        return x;
    });

    CROW_ROUTE(app, "/questions/get-all")(SurveyController::getQuestions);

    // json list response
    CROW_ROUTE(app, "/json_list")
    ([] {
        crow::json::wvalue x(crow::json::wvalue::list({1, 2, 3}));
        return x;
    });


    // TODO: GET REQUEST with params
    // -----------------------------------------------------------------------------------------------------------------
    CROW_ROUTE(app, "/hello/<int>")
    ([](int count) {
        if (count > 100)
            return crow::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
    });

    // example which uses only response as a parameter without request being a parameter.
    CROW_ROUTE(app, "/add/<int>/<int>")
    ([](crow::response &res, int a, int b) {
        std::ostringstream os;
        os << a + b;
        res.write(os.str());
        res.end();
    });

    // Compile error with message "Handler type is mismatched with URL paramters"
    //CROW_ROUTE(app,"/another/<int>")
    //([](int a, int b){
    //return crow::response(500);
    //});


    // TODO: POST REQUEST
    // -----------------------------------------------------------------------------------------------------------------
    CROW_ROUTE(app, "/add_json")
            .methods("POST"_method)([](const crow::request &req) {
                auto x = crow::json::load(req.body);
                if (!x)
                    return crow::response(400);
                int sum = x["a"].i() + x["b"].i();
                std::ostringstream os;
                os << sum;
                return crow::response{os.str()};
            });

#if 0
    {
        "userId": 1,
        "questionId": 1,
        "content": "Answer of the first question, by the user PowerCell46."
    }
#endif
    CROW_ROUTE(app, "/survey/submit")
            .methods("POST"_method)(SurveyController::submitQuestion);


    CROW_ROUTE(app, "/params")
    ([](const crow::request &req) {
        std::ostringstream os;
        os << "Params: " << req.url_params << "\n\n";
        os << "The key 'foo' was " << (req.url_params.get("foo") == nullptr ? "not " : "") << "found.\n";
        if (req.url_params.get("pew") != nullptr) {
            double countD = crow::utility::lexical_cast<double>(req.url_params.get("pew"));
            os << "The value of 'pew' is " << countD << '\n';
        }
        auto count = req.url_params.get_list("count");
        os << "The key 'count' contains " << count.size() << " value(s).\n";
        for (const auto &countVal: count) {
            os << " - " << countVal << '\n';
        }
        return crow::response{os.str()};
    });


    // TODO: PATCH request
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, "/patch_example")
            .methods("PATCH"_method)
            ([](const crow::request &req) {
                // Retrieve the request body
                auto body = req.body;

                CROW_LOG_INFO << "Received PATCH body: " << body;

                crow::response res(200);
                res.write("Patch request processed.");
                return res;
            });


    // TODO: DELETE request
    // -----------------------------------------------------------------------------------------------------------------

    CROW_ROUTE(app, "/item/<int>")
            .methods("DELETE"_method)
            ([](int submissionId) {

                CROW_LOG_INFO << "Submission Id to delete: " << submissionId;

                return crow::response(200, "Submission deleted successfully.");
            });


    // ignore all log
    // -----------------------------------------------------------------------------------------------------------------
    crow::logger::setLogLevel(crow::LogLevel::Debug);
    //crow::logger::setHandler(std::make_shared<ExampleLogHandler>());

    app.port(18080)
            .server_name("CrowCpp")
            .multithreaded()
            .run();
}

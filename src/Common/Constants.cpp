#include "Constants.h"
#include <cstdlib>


char CSV_DELIMITER = std::getenv("CSV_DELIMITER") ? std::getenv("CSV_DELIMITER")[0] : ',';

std::string SERVER_NAME = "CrowSurvey";

int SERVER_PORT = 18080;
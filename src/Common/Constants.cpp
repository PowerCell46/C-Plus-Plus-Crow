#include "Constants.h"
#include <cstdlib>

#define DEFAULT_CSV_DELIMITER ','

char CSV_DELIMITER = std::getenv("CSV_DELIMITER") ? std::getenv("CSV_DELIMITER")[0] : DEFAULT_CSV_DELIMITER;

std::string SERVER_NAME = "CrowSurvey";

int SERVER_PORT = 18080;
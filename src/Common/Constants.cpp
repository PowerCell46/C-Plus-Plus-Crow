#include "Constants.h"
#include <cstdlib>


char CSV_DELIMITER = std::getenv("CSV_DELIMITER") ? std::getenv("CSV_DELIMITER")[0] : ',';
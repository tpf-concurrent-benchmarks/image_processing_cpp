#include <json.hpp>
#include <string>

nlohmann::json getDataFromJsonFile(const char *dataPath);
std::string getPullPort();
std::string getBrokerFromSizeHost();

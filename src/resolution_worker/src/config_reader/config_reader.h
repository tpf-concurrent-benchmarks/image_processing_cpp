#include <json.hpp>
#include <string>
#include <cstdint>

nlohmann::json getDataFromJsonFile(const char *dataPath);
std::string getBrokerFromFormatHost();
std::string getBrokerFromSizeHost();
std::string getPushPort();
std::string getPullPort();
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getNodeId();
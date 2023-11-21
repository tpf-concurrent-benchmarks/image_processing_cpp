#include <cstdint>
#include <json.hpp>
#include <string>

nlohmann::json getDataFromJsonFile(const char *dataPath);
std::string getPullPort();
std::string getPushPort();
std::string getBrokerFromSizeHost();
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getNodeId();
std::string getManagerHost();
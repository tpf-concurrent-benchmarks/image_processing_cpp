#include <json.hpp>
#include <string>
#include <cstdint>

nlohmann::json getDataFromJsonFile(const char *dataPath);
std::string getPullPort();
std::string getBrokerFromSizeHost();
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getNodeId();
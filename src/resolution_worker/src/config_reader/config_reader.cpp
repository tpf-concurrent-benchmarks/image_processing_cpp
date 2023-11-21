#include <fstream>
#include <iostream>
#include <json.hpp>
#include <random>
#include <string>

std::ifstream readFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Error: Could not open the file: " << path << std::endl;
        exit(1);
    }
    return file;
}

nlohmann::json configFileToJson(std::ifstream &configFile)
{
    nlohmann::json configData;
    configFile >> configData;
    return configData;
}

nlohmann::json getDataFromJsonFile(const char *dataPath)
{
    std::ifstream dataFile = readFile(dataPath);
    nlohmann::json data = configFileToJson(dataFile);
    return data;
}

std::string getBrokerFromFormatHost()
{
    const char *host = "broker_format_to_resolution";
    if (getenv("ENV") != nullptr && std::string(getenv("ENV")) == "LOCAL")
    {
        host = "localhost";
    }
    return host;
}

std::string getBrokerFromSizeHost()
{
    const char *host = "broker_resolution_to_size";
    if (getenv("ENV") != nullptr && std::string(getenv("ENV")) == "LOCAL")
    {
        host = "localhost";
    }
    return host;
}

std::string getPushPort()
{
    const char *pushPort = "5558";
    char *pushPortFromEnv = getenv("PUSH_PORT");
    if (pushPortFromEnv != nullptr)
    {

        pushPort = pushPortFromEnv;
    }
    return pushPort;
}

std::string getPullPort()
{
    const char *pullPort = "5557";
    char *pullPortFromEnv = getenv("PULL_PORT");
    if (pullPortFromEnv != nullptr)
    {

        pullPort = pullPortFromEnv;
    }
    return pullPort;
}

uint16_t getGraphitePort()
{
    return 8125;
}

std::string getGraphiteHost()
{
    const char *graphiteHost = "graphite";
    if (getenv("ENV") != nullptr && std::string(getenv("ENV")) == "LOCAL")
    {
        graphiteHost = "localhost";
    }
    return graphiteHost;
}

std::string generateRandomID(int length)
{
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string result;
    for (int i = 0; i < length; ++i)
    {
        result += alphanum[dis(gen)];
    }

    return result;
}

std::string getNodeId()
{
    std::basic_string<char> nodeId = generateRandomID(10);
    char *nodeIdFromEnv = getenv("NODE_ID");
    if (nodeIdFromEnv != nullptr)
    {
        nodeId = nodeIdFromEnv;
    }
    return nodeId;
}

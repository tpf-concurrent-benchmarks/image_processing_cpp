#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>

std::ifstream readFile(const std::string& path)
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
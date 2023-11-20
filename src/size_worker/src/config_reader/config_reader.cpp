#include <cstdlib>
#include <string>
#include <random>

std::string getBrokerFromSizeHost()
{
    const char *host = "broker_resolution_to_size";
    if (getenv("ENV") != nullptr && std::string(getenv("ENV")) == "LOCAL")
    {
        host = "localhost";
    }
    return host;
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

#include <cstdlib>
#include <string>

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
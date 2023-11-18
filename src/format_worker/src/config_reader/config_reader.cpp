#include <string>

std::string getManagerHost()
{
    const char *host = "manager";
    if (getenv("ENV") != nullptr && std::string(getenv("ENV")) == "LOCAL")
    {
        host = "localhost";
    }
    return host;
}

std::string getBrokerHost()
{
    const char *host = "broker_format_to_resolution";
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
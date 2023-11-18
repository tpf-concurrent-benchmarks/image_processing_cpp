#include <cstdlib>
#include <string>

int getNWorkers()
{
    int nWorkers = 1;
    char *nWorkersFromEnv = getenv("N_WORKERS");
    if (nWorkersFromEnv != nullptr)
    {
        nWorkers = atoi(nWorkersFromEnv);
    }
    return nWorkers;
}

std::string getPushPort()
{
    const char *pushPort = "5557";
    char *pushPortFromEnv = getenv("PUSH_PORT");
    if (pushPortFromEnv != nullptr)
    {

        pushPort = pushPortFromEnv;
    }
    return pushPort;
}

std::string getPullPort()
{
    const char *pushPort = "5558";
    char *pushPortFromEnv = getenv("PUSH_PORT");
    if (pushPortFromEnv != nullptr)
    {

        pushPort = pushPortFromEnv;
    }
    return pushPort;
}
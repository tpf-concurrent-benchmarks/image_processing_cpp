#include "config_reader.h"
#include <algorithm>
#include <iostream>

std::vector<std::pair<std::string, std::string>> getImagesInDirectory(const fs::path &directory)
{

    if (!fs::exists(directory) || !fs::is_directory(directory))
    {
        std::cerr << "Directory " << directory << " does not exist or is not a directory" << std::endl;
        return {};
    }

    std::vector<std::pair<std::string, std::string>> imageFiles;

    for (const auto &entry : fs::directory_iterator(directory))
    {

        if (fs::is_regular_file(entry.path()))
        {
            std::string extension = entry.path().extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            if (extension == ".jpg" || extension == ".png" || extension == ".gif")
            {
                imageFiles.emplace_back(entry.path().stem().string(), extension);
            }
        }
    }

    return imageFiles;
}

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

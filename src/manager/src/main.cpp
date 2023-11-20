#include "config_reader/config_reader.h"
#include "constants.h"
#include "protocol/protocol.h"
#include <csignal>
#include <filesystem>
#include <iostream>
#include "cpp-statsd-client/StatsdClient.hpp"
#include <chrono>

int main()
{

    std::chrono::milliseconds start_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), "manager"};

    Protocol protocol(getPushPort());
    int nWorkers = getNWorkers();

    fs::path imagesDirectory = "../../shared_vol/input/";
    const std::vector<fs::path> &imagesFiles = getImagesInDirectory(imagesDirectory);

    if (imagesFiles.empty())
    {
        std::cerr << "No imagesFiles found in directory " << imagesDirectory << std::endl;
        exit(-1);
    }

    // For sync purposes
    sleep(20);

    for (const auto &image : imagesFiles)
    {
        protocol.send(image.string());
    }

    for (int i = 0; i < nWorkers; ++i)
    {
        protocol.send(Constants::STOP_MESSAGE);
    }

    protocol.close();

    std::chrono::milliseconds end_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
    statsdClient.gauge("completion_time", completion_time.count(), 1, {});

    return 0;
}
#include "config_reader/config_reader.h"
#include "constants.h"
#include "cpp-statsd-client/StatsdClient.hpp"
#include "protocol/protocol.h"
#include <chrono>
#include <csignal>
#include <filesystem>
#include <iostream>

int main()
{

    std::chrono::milliseconds start_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), "manager"};

    Protocol protocol(getPushPort(), getPullPort());

    fs::path imagesDirectory = "../../shared_vol/input/";
    const std::vector<fs::path> &imagesFiles = getImagesInDirectory(imagesDirectory);

    if (imagesFiles.empty())
    {
        std::cerr << "No imagesFiles found in directory " << imagesDirectory << std::endl;
        exit(-1);
    }

    const size_t jobsToBeDone = imagesFiles.size();

    std::thread t([&protocol, &jobsToBeDone]() {
        int jobsDone = 0;
        while (jobsDone < jobsToBeDone)
        {
            std::string message = protocol.receive();
            if (message == Constants::END_WORK_MESSAGE)
            {
                jobsDone++;
            }
            else
            {
                std::cout << "Unknown message received" << std::endl;
            }
        }
    });

    // For sync purposes
    std::this_thread::sleep_for(std::chrono::seconds(20));

    for (const auto &image : imagesFiles)
    {
        protocol.send(image.string());
    }

    t.join();

    protocol.sendStopMessage(Constants::STOP_MESSAGE);
    std::cout << "Sent stop message to all workers" << std::endl;

    protocol.close();

    std::chrono::milliseconds end_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
    statsdClient.gauge("completion_time", completion_time.count(), 1, {});

    return 0;
}
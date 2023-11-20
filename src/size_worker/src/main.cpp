#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/crop.cpp>
#include "cpp-statsd-client/StatsdClient.hpp"
#include <chrono>

int main()
{
    std::string brokerHost = getBrokerFromSizeHost();
    std::string pullPort = getPullPort();
    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), getNodeId()};
    // Desired size is here
    nlohmann::json sizeConfig = getDataFromJsonFile("../resources/config.json");

    Protocol protocol(brokerHost, pullPort);

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
        }
        else
        {
            std::string imageName = message.substr(message.find_last_of('/') + 1);

            std::chrono::milliseconds start_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

            crop_centered(message, "../../shared_vol/cropped/" + imageName, 100, 100);

            std::chrono::milliseconds end_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
            statsdClient.timing("work_time", completion_time.count(), 1);
            statsdClient.increment("results_produced");
            
            // std::cout << "Cropped image: " << imageName << std::endl;
        }
    }

    protocol.close();
}

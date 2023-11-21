#include "config_reader/config_reader.h"
#include "cpp-statsd-client/StatsdClient.hpp"
#include "protocol/protocol.h"
#include <chrono>
#include <constants.h>
#include <image_manipulation/crop.cpp>

int main()
{
    std::string brokerHost = getBrokerFromSizeHost();
    std::string pullPort = getPullPort();
    std::string pushPort = getPushPort();
    std::string managerHost = getManagerHost();
    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), getNodeId()};
    nlohmann::json sizeConfig = getDataFromJsonFile("../resources/config.json");

    Protocol protocol(brokerHost, managerHost, pushPort, pullPort);

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            protocol.send(Constants::END_WORK_MESSAGE);
        }
        else
        {
            std::string imageName = message.substr(message.find_last_of('/') + 1);

            std::chrono::milliseconds start_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

            crop_centered(message, "../../shared_vol/cropped/" + imageName, sizeConfig["targetWidth"],
                          sizeConfig["targetHeight"]);

            std::chrono::milliseconds end_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
            std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
            statsdClient.timing("work_time", completion_time.count(), 1);
            statsdClient.increment("results_produced");
        }
    }

    protocol.close();
}

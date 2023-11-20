#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/change_resolution.cpp>
#include "cpp-statsd-client/StatsdClient.hpp"
#include <chrono>

int main()
{
    nlohmann::json resolutionConfig = getDataFromJsonFile("../resources/config.json");
    std::string brokerFromSizeHost = getBrokerFromSizeHost();
    std::string brokerFromFormatHost = getBrokerFromFormatHost();
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();

    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), getNodeId()};

    Protocol protocol(brokerFromFormatHost, brokerFromSizeHost, pushPort, pullPort);

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            protocol.send(message);
        }
        else
        {
            std::string imageName = message.substr(message.find_last_of('/') + 1);

            std::chrono::milliseconds start_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

            change_resolution(message, resolutionConfig["targetWidth"], resolutionConfig["targetHeight"],
                "../../shared_vol/resized/" + imageName);

            std::chrono::milliseconds end_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
            statsdClient.timing("work_time", completion_time.count(), 1);
            statsdClient.increment("results_produced");

            protocol.send("../../shared_vol/resized/" + imageName);
        }
    }

    protocol.close();
}

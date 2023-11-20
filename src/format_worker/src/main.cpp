#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/change_format.cpp>
#include "cpp-statsd-client/StatsdClient.hpp"
#include <chrono>

int main()
{
    std::string managerHost = getManagerHost();
    std::string brokerHost = getBrokerHost();
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();

    Statsd::StatsdClient statsdClient{getGraphiteHost(), getGraphitePort(), getNodeId()};

    Protocol protocol(managerHost, brokerHost, pushPort, pullPort);

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
            std::string newImageName = imageName.substr(0, imageName.find_last_of('.')) + ".png";

            std::chrono::milliseconds start_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

            change_format(message, "../../shared_vol/formatted/" + newImageName);

            std::chrono::milliseconds end_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
            statsdClient.timing("work_time", completion_time.count(), 1);
            statsdClient.increment("results_produced");
            
            protocol.send("../../shared_vol/formatted/" + newImageName);
        }
    }

    protocol.close();
}
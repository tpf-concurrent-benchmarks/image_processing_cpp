#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/change_format.cpp>

int main()
{
    std::string managerHost = getManagerHost();
    std::string brokerHost = getBrokerHost();
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();

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
            change_format(message, "../../shared_vol/formatted/" + newImageName);
            protocol.send("../../shared_vol/formatted/" + newImageName);
        }
    }

    protocol.close();
}
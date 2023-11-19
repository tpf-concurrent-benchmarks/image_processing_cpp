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
            change_format(message, "../../shared_vol/formatted/");
            std::string imageName = message.substr(message.find_last_of('/') + 1);
            protocol.send("../../shared_vol/formatted/" + imageName);
        }
    }

    protocol.close();
}
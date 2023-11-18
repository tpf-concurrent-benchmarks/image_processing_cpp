#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/change_resolution.cpp>

int main()
{
    std::string brokerFromSizeHost = getBrokerFromSizeHost();
    std::string brokerFromFormatHost = getBrokerFromFormatHost();
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();

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
            change_resolution(message, 100, 100, "./shared/resized/" + imageName);
            protocol.send("./shared/resized/" + imageName);
        }
    }

    protocol.close();
}

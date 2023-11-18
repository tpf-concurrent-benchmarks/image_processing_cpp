#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <image_manipulation/crop.cpp>

int main()
{
    std::string brokerHost = getBrokerFromSizeHost();
    std::string pullPort = getPullPort();

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
            // TODO: what are x and y in this function?
            // crop(message, "./shared/cropped/" + imageName, 100, 100);
        }
    }

    protocol.close();
}

#include "../../shared/constants.h"
#include "config_reader/config_reader.h"
#include "protocol/protocol.h"

int main()
{

    Protocol protocol(getPushPort(), getPullPort());
    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            continue;
        }
        protocol.send(message);
    }

    protocol.close();
}

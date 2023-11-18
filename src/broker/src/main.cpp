#include "../../shared/constants.h"
#include "config_reader/config_reader.h"
#include "protocol/protocol.h"

int main()
{

    Protocol protocol(getPushPort(), getPullPort());
    int nWorkers = getNWorkers();
    int finishedWorkers = 0;

    while (finishedWorkers < nWorkers)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            finishedWorkers++;
        }
        protocol.send(message);
    }

    protocol.close();
}

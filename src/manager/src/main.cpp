#include "config_reader/config_reader.h"
#include "constants.h"
#include "protocol/protocol.h"
#include <csignal>
#include <filesystem>
#include <iostream>

int main()
{

    Protocol protocol(getPushPort());
    int nWorkers = getNWorkers();

    fs::path imagesDirectory = "../../shared_vol/input/";
    const std::vector<fs::path> &imagesFiles = getImagesInDirectory(imagesDirectory);

    if (imagesFiles.empty())
    {
        std::cerr << "No imagesFiles found in directory " << imagesDirectory << std::endl;
        exit(-1);
    }

    // For sync purposes
    sleep(20);

    for (const auto &image : imagesFiles)
    {
        protocol.send(image.string());
    }

    for (int i = 0; i < nWorkers; ++i)
    {
        protocol.send(Constants::STOP_MESSAGE);
    }

    protocol.close();

    return 0;
}
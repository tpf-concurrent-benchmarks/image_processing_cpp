#include "../../shared/constants.h"
#include "config_reader/config_reader.h"
#include "protocol/protocol.h"
#include <filesystem>
#include <iostream>

int main()
{

    Protocol protocol(getPushPort());
    int nWorkers = getNWorkers();

    fs::path imagesDirectory = "./shared/input";
    const std::vector<std::pair<std::string, std::string>> &imagesFiles = getImagesInDirectory(imagesDirectory);

    if (imagesFiles.empty())
    {
        std::cerr << "No imagesFiles found in directory " << imagesDirectory << std::endl;
        exit(-1);
    }

    for (const auto &image : imagesFiles)
    {
        // This path is the shared directory between all services
        const std::string &imagePath = imagesDirectory.string() + image.first + image.second;
        protocol.send(imagePath);
    }

    for (int i = 0; i < nWorkers; ++i)
    {
        protocol.send(Constants::STOP_MESSAGE);
    }

    protocol.close();

    return 0;
}
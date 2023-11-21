#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> getImagesInDirectory(const fs::path &directory);
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getPushPort();
std::string getPullPort();
int getNWorkers();

#endif // CONFIG_READER_H
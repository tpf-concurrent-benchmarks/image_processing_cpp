#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::pair<std::string, std::string>> getImagesInDirectory(const fs::path &directory);
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getPushPort();
int getNWorkers();

#endif // CONFIG_READER_H
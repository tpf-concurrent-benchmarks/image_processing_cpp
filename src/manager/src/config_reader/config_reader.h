#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::pair<std::string, std::string>> getImagesInDirectory(const fs::path& directory);
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getPushPort();

#endif // CONFIG_READER_H
#include <iostream>
#include <string>
#include "image_manipulation/change_resolution.cpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "image_manipulation/stb_image.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "image_manipulation/stb_image_write.h"

int main() {
    std::string path = "/home/civa/image_processing_cpp/src/image_processing/resources/rust.jpeg";
    // int width, height, channels;
    // unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    int new_width = 100;
    int new_height = 100;
    std::string output_path = "/home/civa/image_processing_cpp/src/image_processing/resources/rust.png";
    change_resolution(path, new_width, new_height, output_path);
    // stbi_write_png(output_path.c_str(), width, height, channels, image, width * channels);
    return 0;
}
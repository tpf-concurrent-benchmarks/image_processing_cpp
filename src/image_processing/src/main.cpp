#include <iostream>
#include <string>
#include "image_manipulation/change_resolution.cpp"
#define cimg_display 0
#include "CImg.h"
int main() {
    std::string path = "src/image_processing/resources/rust.jpeg";
    int new_width = 100;
    int new_height = 100;
    std::string output_path = "src/image_processing/resources/rust_resized.jpeg";
    change_resolution(path, new_width, new_height, output_path);
    return 0;
}
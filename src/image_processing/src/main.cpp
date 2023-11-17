#include <iostream>
#include <string>
// #include "image_manipulation/change_resolution.cpp"
// #include "image_manipulation/change_format.cpp"
#include "image_manipulation/crop.cpp"

int main() {
    std::string path = "/home/civa/image_processing_cpp/src/image_processing/resources/rust.png";

    int new_width = 100;
    int new_height = 100;

    std::string output_path = "/home/civa/image_processing_cpp/src/image_processing/resources/rust_crop.png";

    // change_resolution(path, new_width, new_height, output_path);

    // change_format(path, output_path);

    crop_centered(path, output_path, 100, 100);
    return 0;
}
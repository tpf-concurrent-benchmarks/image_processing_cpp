#include "CImg.h"
#include <string>

void change_resolution(std::string path, int new_width, int new_height, std::string output_path) {
    // Load the image
    cimg_library::CImg<unsigned char> image(path.c_str());

    // Display the original image
    image.display("Original Image");

    // Resize the image
    cimg_library::CImg<unsigned char> resized_image = image.resize(new_width, new_height);

    // Display the resized image
    resized_image.display("Resized Image");

    resized_image.save(output_path.c_str());
}
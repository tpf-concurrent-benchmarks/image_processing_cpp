#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// This function changes the format of an image from any format to PNG
void change_format(const std::string& path, const std::string& output_path)
{
    int input_width, input_height, input_channels;
    unsigned char *input_image = stbi_load(path.c_str(), &input_width, &input_height, &input_channels, 0);

    stbi_write_png_compression_level = 9;
    stbi_write_png(output_path.c_str(), input_width, input_height, input_channels, input_image,
                   input_width * input_channels);

    stbi_image_free(input_image);
}
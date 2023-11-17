#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

void change_resolution(std::string path, int output_width, int output_height, std::string output_path)
{
    int input_width, input_height, input_channels;
    unsigned char *input_image = stbi_load(path.c_str(), &input_width, &input_height, &input_channels, 0);

    int output_channels = input_channels;

    unsigned char *output_image = new unsigned char[output_width * output_height * output_channels];

    stbir_resize_uint8_linear(input_image, input_width, input_height, 0, output_image, output_width, output_height, 0,
                              static_cast<stbir_pixel_layout>(output_channels));

    stbi_write_png(output_path.c_str(), output_width, output_height, output_channels, output_image,
                   output_width * output_channels);

    stbi_image_free(input_image);
    delete[] output_image;
}
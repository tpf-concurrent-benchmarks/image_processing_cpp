#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <string>

void _crop(unsigned char *input_image, const std::string& output_path, int x, int y, int width, int height, int input_width,
           int input_height, int input_channels)
{
    x = std::max(0, std::min(x, input_width - 1));
    y = std::max(0, std::min(y, input_height - 1));
    width = std::min(width, input_width - x);
    height = std::min(height, input_height - y);

    auto *cropped_image = new unsigned char[width * height * input_channels];

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int c = 0; c < input_channels; ++c)
            {
                cropped_image[(j * width + i) * input_channels + c] =
                    input_image[((j + y) * input_width + (i + x)) * input_channels + c];
            }
        }
    }

    stbi_write_png(output_path.c_str(), width, height, input_channels, cropped_image, width * input_channels);

    stbi_image_free(input_image);
    delete[] cropped_image;
}

void crop(const std::string& path, const std::string& output_path, int x, int y, int width, int height)
{
    int input_width, input_height, input_channels;
    unsigned char *input_image = stbi_load(path.c_str(), &input_width, &input_height, &input_channels, 0);

    _crop(input_image, output_path, x, y, width, height, input_width, input_height, input_channels);
}

void crop_centered(std::string path, std::string output_path, int width, int height)
{
    int input_width, input_height, input_channels;
    unsigned char *input_image = stbi_load(path.c_str(), &input_width, &input_height, &input_channels, 0);

    int x = (input_width - width) / 2;
    int y = (input_height - height) / 2;

    _crop(input_image, output_path, x, y, width, height, input_width, input_height, input_channels);
}
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


unsigned char *load_image(const char *filename, int &width, int &height)
{
    int actual_channels;
    unsigned char* data = stbi_load(filename, &width, &height, &actual_channels, 3);
    if (data == nullptr) {
        std::cerr << "Failed to load image: " << filename << std::endl;
    }

    return data;
}

void write_image(const char* filename, int width, int height, int channels, unsigned char* data) {
    int success = stbi_write_jpg(filename, width, height, channels, data, 100);
    
    if (success) {
        std::cout << "Successfully saved: " << filename << " (" << width << "x" << height << ")\n";
    } else {
        std::cerr << "Failed to write image: " << filename << "\n";
    }
}

void free_image(unsigned char* data) {
    if (data != nullptr) {
        stbi_image_free(data);
    }
}

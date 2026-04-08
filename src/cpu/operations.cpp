#include "api.h"
#include <cmath>
#include <algorithm>

void vector_add_cpu(float* a, float* b, float* c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void cpu_grayscale(unsigned char* input_rgb, unsigned char* output_gray, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            unsigned char r = input_rgb[3 * index];
            unsigned char g = input_rgb[3 * index + 1];
            unsigned char b = input_rgb[3 * index + 2];

            float gray = 0.299f * r + 0.587f * g + 0.114f * b;
            output_gray[index] = static_cast<unsigned char>(std::round(gray));
        }
    }
}

void cpu_blur(unsigned char* input, unsigned char* blurred, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int neighborX = x + dx;
                    int neighborY = y + dy;

                    int safeX = std::clamp(neighborX, 0, width - 1);
                    int safeY = std::clamp(neighborY, 0, height - 1);

                    int index = width * safeY + safeX;
                    sum += input[index];
                }
            }
            int centerIndex = width * y + x;
            float mean = sum / 9.0f;
            blurred[centerIndex] = static_cast<unsigned char>(std::round(mean));
        }
    }
}
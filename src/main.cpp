#include <iostream>
#include <vector>

#include "api.h"
#include "utils.h"
#include "benchmark.h"

int main() {
    // simple vector add
    int n = 1 << 20;

    std::cout << "Starting CPU Benchmarks for vector add with " << n << "elements \n";

    std::vector<float> a(n, 1.0f), b(n, 2.0f), c(n);

    BENCHMARK_CPU(vector_add_cpu(a.data(), b.data(), c.data(), n));
    BENCHMARK_GPU(vector_add_gpu(a.data(), b.data(), c.data(), n));

    // image grayscaling and blurring
    int width, height;
    unsigned char* img = load_image("data/input/input.jpg", width, height);

    unsigned char* output_gray = new unsigned char[width * height];
    unsigned char* output_blur = new unsigned char[width * height];
    
    std::cout << "Starting CPU Benchmarks for " << width << "x" << height << " image...\n";
    
    BENCHMARK_CPU(cpu_grayscale(img, output_gray, width, height));
    BENCHMARK_CPU(cpu_blur(output_gray, output_blur, width, height));

    write_image("data/output/output_gray.jpg", width, height, 1, output_gray);
    write_image("data/output/output_blur.jpg", width, height, 1, output_blur);

    free_image(img);

    delete[] output_gray;
    delete[] output_blur;

    return 0;
}
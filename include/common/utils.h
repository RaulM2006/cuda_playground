#pragma once
#include <iostream>
#include <cuda_runtime.h>

#define CUDA_CHECK(call) \
{ \
    cudaError_t err = call; \
    if (err != cudaSuccess) { \
        std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl; \
        exit(1); \
    } \
}

unsigned char* load_image(const char* filename, int& width, int& height);
void write_image(const char* filename, int width, int height, int channels, unsigned char* data);
void free_image(unsigned char* data);
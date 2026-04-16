#include "api.h"
#include <cuda_runtime.h>
#include <algorithm>

// Kernel
__global__ void vector_add_kernel(float* a, float* b, float* c, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        c[idx] = a[idx] + b[idx];
    }
}

// Wrapper
void vector_add_gpu(float* a, float* b, float* c, int n) {
    float *d_a, *d_b, *d_c;

    cudaMalloc(&d_a, n * sizeof(float));
    cudaMalloc(&d_b, n * sizeof(float));
    cudaMalloc(&d_c, n * sizeof(float));

    cudaMemcpy(d_a, a, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n * sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    vector_add_kernel<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, n * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}

// Kernel
__global__ void grayscale_kernel(unsigned char* img, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int pixel_index = width * y + x;
        unsigned char r = img[3 * pixel_index];
        unsigned char g = img[3 * pixel_index + 1];
        unsigned char b = img[3 * pixel_index + 2];

        float gray = 0.299f * r + 0.587f * g + 0.114f * b;
        output[pixel_index] = static_cast<unsigned char>(roundf(gray));
    }
}

// Wrapper
void gpu_grayscale(unsigned char *input_rgb, unsigned char *outputgray, int width, int height)
{
    unsigned char *d_img, *d_out;

    cudaMalloc(&d_img, 3 * width * height * sizeof(unsigned char));
    cudaMalloc(&d_out, width * height * sizeof(unsigned char));

    cudaMemcpy(d_img, input_rgb, 3 * width * height * sizeof(unsigned char), cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    int x_blocks = (width + blockSize.x - 1) / blockSize.x;
    int y_blocks = (height + blockSize.y - 1) / blockSize.y;

    dim3 gridSize(x_blocks, y_blocks);

    grayscale_kernel<<<gridSize, blockSize>>>(d_img, d_out, width, height);

    cudaMemcpy(outputgray, d_out, height * width * sizeof(unsigned char), cudaMemcpyDeviceToHost);

    cudaFree(d_img);
    cudaFree(d_out);
}

// Kernel
__global__ void blur_kernel(unsigned char* img, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int sum = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int neighborX = x + dx;
                int neighborY = y + dy;

                int safeX = min(max(neighborX, 0), width - 1);
                int safeY = min(max(neighborY, 0), height - 1);

                int index = width * safeY + safeX;
                sum += img[index];
            }
        }
        int centerIndex = width * y + x;
        float mean = sum / 9.0f;
        output[centerIndex] = static_cast<unsigned char>(roundf(mean));
    }
}

// Wrapper
void gpu_blur(unsigned char * input, unsigned char * blurred, int width, int height)
{
        unsigned char *d_img, *d_out;

    cudaMalloc(&d_img, width * height * sizeof(unsigned char));
    cudaMalloc(&d_out, width * height * sizeof(unsigned char));

    cudaMemcpy(d_img, input, width * height * sizeof(unsigned char), cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    int x_blocks = (width + blockSize.x - 1) / blockSize.x;
    int y_blocks = (height + blockSize.y - 1) / blockSize.y;

    dim3 gridSize(x_blocks, y_blocks);

    blur_kernel<<<gridSize, blockSize>>>(d_img, d_out, width, height);

    cudaMemcpy(blurred, d_out, height * width * sizeof(unsigned char), cudaMemcpyDeviceToHost);

    cudaFree(d_img);
    cudaFree(d_out);
}

#pragma once

// CPU
void vector_add_cpu(float* a, float* b, float* c, int n);
void cpu_grayscale(unsigned char* input_rgb, unsigned char* output_gray, int width, int height);
void cpu_blur(unsigned char* input, unsigned char* blurred, int width, int height);

// GPU
void vector_add_gpu(float* a, float* b, float* c, int n);
void gpu_grayscale(unsigned char* input_rgb, unsigned char* outputgray, int width, int height);
void gpu_blur(unsigned char* input, unsigned char* blurred, int width, int height);

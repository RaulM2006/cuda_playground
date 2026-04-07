#pragma once
#include <chrono>
#include <cuda_runtime.h>

// CPU timer
class CPUTimer {
    std::chrono::high_resolution_clock::time_point start_, end_;
public:
    void start() { start_ = std::chrono::high_resolution_clock::now(); }
    void stop() { end_ = std::chrono::high_resolution_clock::now(); }
    double elapsed_ms() {
        return std::chrono::duration<double, std::milli>(end_ - start_).count();
    }
};

// GPU timer
class GPUTimer {
    cudaEvent_t start_, stop_;
public:
    GPUTimer() {
        cudaEventCreate(&start_);
        cudaEventCreate(&stop_);
    }
    void start() { cudaEventRecord(start_); }
    void stop() {
        cudaEventRecord(stop_);
        cudaEventSynchronize(stop_);
    }
    float elapsed_ms() {
        float ms;
        cudaEventElapsedTime(&ms, start_, stop_);
        return ms;
    }
};
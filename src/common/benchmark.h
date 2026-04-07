#pragma once
#include <iostream>
#include "timer.h"

#define BENCHMARK_CPU(func) \
{ \
    CPUTimer t; \
    t.start(); \
    func; \
    t.stop(); \
    std::cout << #func << " CPU: " << t.elapsed_ms() << " ms\n"; \
}

#define BENCHMARK_GPU(func) \
{ \
    GPUTimer t; \
    t.start(); \
    func; \
    t.stop(); \
    std::cout << #func << " GPU: " << t.elapsed_ms() << " ms\n"; \
}
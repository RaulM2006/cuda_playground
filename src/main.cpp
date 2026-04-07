#include <iostream>
#include <vector>

#include "api.h"
#include "benchmark.h"

int main() {
    int n = 1 << 20;

    std::vector<float> a(n, 1.0f), b(n, 2.0f), c(n);

    BENCHMARK_CPU(vector_add_cpu(a.data(), b.data(), c.data(), n));
    BENCHMARK_GPU(vector_add_gpu(a.data(), b.data(), c.data(), n));

    return 0;
}
cmake_minimum_required(VERSION 3.18)
project(cuda_playground LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# This helps CMake find CUDA on machines where it might be in a non-standard path
find_package(CUDAToolkit REQUIRED)

add_executable(main
    src/main.cpp
    src/cpu/operations.cpp
    src/gpu/kernels.cu
    src/common/utils.cpp
)

# Use target_include_directories instead of include_directories
# This makes the project more modular
target_include_directories(main PRIVATE 
    include 
    include/common
    external
    ${CUDAToolkit_INCLUDE_DIRS}
)

# Link the CUDA Runtime
target_link_libraries(main PRIVATE CUDA::cudart)

set_target_properties(main PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    # This ensures the .exe ends up in a predictable place for some scripts
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
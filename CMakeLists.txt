cmake_minimum_required(VERSION 3.19)
project(friends CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(friends main.cpp data_load.h)

set(CMAKE_CXX_STANDARD 14)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3")
endif()


find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(friends OpenMP::OpenMP_CXX)
endif()

message(STATUS "${benchmark_INCLUDE_DIRS}")

# include Google Benchmarks
find_package(benchmark REQUIRED)
target_link_libraries(friends benchmark::benchmark)
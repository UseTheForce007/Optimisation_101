file(GLOB_RECURSE BENCHMARK_SOURCES "*.cpp")

# Exclude the standalone MPI benchmark from the main benchmarks executable
list(REMOVE_ITEM BENCHMARK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mpi_benchmark_standalone.cpp")

find_package(benchmark REQUIRED)
find_package(MPI REQUIRED)

add_executable(benchmarks ${BENCHMARK_SOURCES})

# Add AVX/AVX2 flags for SIMD support
target_compile_options(benchmarks PRIVATE -mavx -mavx2)

target_include_directories(benchmarks PRIVATE ${PROJECT_SOURCE_DIR}/include ${MPI_INCLUDE_PATH})
target_link_libraries(benchmarks PRIVATE optimisation_101 benchmark::benchmark benchmark::benchmark_main MPI::MPI_CXX)

# Create standalone MPI benchmark executable
add_executable(mpi_benchmark mpi_benchmark_standalone.cpp)
target_compile_options(mpi_benchmark PRIVATE -mavx -mavx2)
target_include_directories(mpi_benchmark PRIVATE ${PROJECT_SOURCE_DIR}/include ${MPI_INCLUDE_PATH})
target_link_libraries(mpi_benchmark PRIVATE optimisation_101 MPI::MPI_CXX)

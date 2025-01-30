file(GLOB_RECURSE BENCHMARK_SOURCES "*.cpp")
find_package(benchmark REQUIRED)

add_executable(benchmarks ${BENCHMARK_SOURCES})

target_include_directories(benchmarks PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(benchmarks PRIVATE optimisation_101 benchmark::benchmark benchmark::benchmark_main)

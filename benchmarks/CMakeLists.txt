file(GLOB_RECURSE BENCHMARK_SOURCES "*.cpp")

add_executable(benchmarks ${BENCHMARK_SOURCES})

target_include_directories(benchmarks PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(benchmarks PRIVATE optimisation_101 benchmark benchmark_main)

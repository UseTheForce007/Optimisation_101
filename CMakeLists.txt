cmake_minimum_required(VERSION 3.15)
project(Optimisation_101)

# Include common settings
include(cmake/CommonSettings.cmake)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)

# Enable testing
enable_testing()

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
endif()

# Add executable for main function
add_executable(main src/main.cpp src/BaseCase.cpp src/Blocking.cpp)

# Custom targets for compiler reports
add_custom_target(static_analysis
    COMMAND scan-build-18
    --use-analyzer=/usr/bin/clang++-18
    -enable-checker core,cplusplus,unix,security
    -o ${CMAKE_BINARY_DIR}/analysis
    -v
    ninja
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running static analysis"
    DEPENDS main
)

add_custom_target(optimization_report
    COMMAND ${CMAKE_COMMAND} -E echo "Generating optimization report..."
    COMMAND clang++ -O3 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -I${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/*.cpp > ${CMAKE_BINARY_DIR}/vectorization_report.txt 2>&1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Clang optimization report"
)

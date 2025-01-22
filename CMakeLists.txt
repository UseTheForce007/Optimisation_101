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

# Custom targets for compiler reports
add_custom_target(static_analysis
    COMMAND ${CMAKE_COMMAND} -E echo "Running Clang static analysis..."
    COMMAND clang++ -Xclang -analyze -fsyntax-only ${CMAKE_SOURCE_DIR}/src/*.cpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Clang static analysis"
)

add_custom_target(optimization_report
    COMMAND ${CMAKE_COMMAND} -E echo "Generating optimization report..."
    COMMAND clang++ -O3 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize ${CMAKE_SOURCE_DIR}/src/*.cpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Clang optimization report"
)

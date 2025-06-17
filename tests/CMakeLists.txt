file(GLOB_RECURSE TEST_SOURCES "*.cpp")
find_package(MPI REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include ${MPI_INCLUDE_PATH})

add_executable(tests ${TEST_SOURCES})

# Add AVX/AVX2 flags for SIMD support
target_compile_options(tests PRIVATE -mavx -mavx2)

target_link_libraries(tests PRIVATE optimisation_101 gtest gtest_main MPI::MPI_CXX)

# Create test that requires MPI runtime
add_test(NAME mpi_tests COMMAND mpirun -np 2 tests --gtest_filter="*ParallelBlockingMPIRows*")
add_test(NAME serial_tests COMMAND tests --gtest_filter="-*ParallelBlockingMPIRows*")

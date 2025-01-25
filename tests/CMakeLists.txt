file(GLOB_RECURSE TEST_SOURCES "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests PRIVATE optimisation_101 gtest gtest_main)

add_test(NAME all_tests COMMAND tests)

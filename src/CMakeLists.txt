file(GLOB_RECURSE SOURCES "*.cpp")

# Remove main.cpp from the list of sources
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_compile_options(-funroll-loops -O3 -mavx2 -march=native)
add_library(optimisation_101 ${SOURCES})

target_include_directories(optimisation_101 PUBLIC ${PROJECT_SOURCE_DIR}/include)

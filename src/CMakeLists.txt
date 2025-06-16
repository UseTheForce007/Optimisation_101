file(GLOB_RECURSE SOURCES "*.cpp")

# Remove main.cpp from the list of sources
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Find MPI package
find_package(MPI REQUIRED)

add_compile_options(-funroll-loops -O3 -mavx2 -march=native -fopenmp -fopenmp=libiomp5)
add_library(optimisation_101 ${SOURCES})

# Link MPI to the library
target_link_libraries(optimisation_101 PUBLIC MPI::MPI_CXX)

target_include_directories(optimisation_101 PUBLIC ${PROJECT_SOURCE_DIR}/include ${MPI_INCLUDE_PATH})

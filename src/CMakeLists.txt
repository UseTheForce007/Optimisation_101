file(GLOB_RECURSE SOURCES "*.cpp")

add_library(optimisation_101 ${SOURCES})

target_include_directories(optimisation_101 PUBLIC ${PROJECT_SOURCE_DIR}/include)

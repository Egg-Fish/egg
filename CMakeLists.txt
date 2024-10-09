cmake_minimum_required(VERSION 3.12)
project(egg)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Option to build examples and tests
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" OFF)

# Add external dependencies (GLFW, GLAD)
add_subdirectory(external/glfw)
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Library source files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

add_library(egg ${LIBRARY_SOURCES})

# Link GLFW and GLAD to the library
target_link_libraries(egg glfw glad)

# Include directories for your library
target_include_directories(egg PUBLIC include)

# Add examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples/example1)
endif()

# Add tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

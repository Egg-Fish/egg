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

# Add Dear ImGUI from submodule
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_BACKEND_DIR ${IMGUI_DIR}/backends)

# Add ImGUI source files
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
)

# Add backend sources for GLFW and OpenGL
set(IMGUI_BACKEND_SOURCES
    ${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES})

# Set include directories for ImGUI and backends
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_BACKEND_DIR})
target_include_directories(imgui PUBLIC external/glfw/include) # Needed for GLFW backend
target_include_directories(imgui PUBLIC external/glad/include) # Needed for GLAD backend

# Library source files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

add_library(egg ${LIBRARY_SOURCES})

# Link GLFW, GLAD, and ImGUI to the library
target_link_libraries(egg glfw glad imgui)

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

cmake_minimum_required(VERSION 3.12)
project(egg)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Option to build examples and tests
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" OFF)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add the DEBUG definition only for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# Add external dependencies (GLFW, GLAD, Assimp, JSON)
add_subdirectory(external/glfw)
add_subdirectory(external/assimp)  # Add Assimp subdirectory
add_subdirectory(external/json)    # Add JSON subdirectory

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

# Add stb_image directory
set(STB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/stb")
# Add GLM
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glm")

# Include stb_image header files
include_directories(${STB_INCLUDE_DIR})

# Library source files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

add_library(egg ${LIBRARY_SOURCES})

# Link GLFW, GLAD, ImGUI, Assimp, and JSON to the egg library
target_link_libraries(egg glfw glad imgui assimp nlohmann_json::nlohmann_json)  # Link JSON

# Include directories for your library
target_include_directories(egg PUBLIC include/egg)
target_include_directories(egg PUBLIC ${STB_INCLUDE_DIR})
target_include_directories(egg PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(egg PUBLIC external/assimp/include)  # Include Assimp headers
target_include_directories(egg PUBLIC external/json/include)    # Include JSON headers

# Add examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples/example1)
    add_subdirectory(examples/example2)
    add_subdirectory(examples/example3)
endif()

# Add tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

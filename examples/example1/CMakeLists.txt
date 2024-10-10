cmake_minimum_required(VERSION 3.12)

# Name the example project
project(example1)

# Add the executable for this example
add_executable(example1 main.cpp)

# Link the OpenGL library and its dependencies
target_link_libraries(example1 PRIVATE egg glfw glad)

# Specify include directories (in case you need to access the library headers)
target_include_directories(example1 PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET example1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/examples/example1 $<TARGET_FILE_DIR:example1>/example1
)
cmake_minimum_required(VERSION 3.12)

# Name the example project
project(example2)

# Add the executable for this example
add_executable(example2 main.cpp)

# Link the OpenGL library and its dependencies
target_link_libraries(example2 PRIVATE egg glfw glad)

# Specify include directories (in case you need to access the library headers)
target_include_directories(example2 PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET example2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/examples/example2 $<TARGET_FILE_DIR:example2>/example2
)
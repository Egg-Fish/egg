cmake_minimum_required(VERSION 3.12)

# Name the example project
project(example3)

# Add the executable for this example
add_executable(example3 main.cpp)

# Link the OpenGL library and its dependencies
target_link_libraries(example3 PRIVATE egg glfw glad)

# Specify include directories (in case you need to access the library headers)
target_include_directories(example3 PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET example3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/examples/example3 $<TARGET_FILE_DIR:example3>/example3
)
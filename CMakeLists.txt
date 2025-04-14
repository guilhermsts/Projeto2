# Set CMAKE minimum required version 
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Projeto2)

# Add the sensorLib folder to the build
add_subdirectory(src/lib)
add_subdirectory(src/unity)

# Add the executable
add_executable(main src/main.c)
add_executable(test src/test.c)

target_compile_options(main PUBLIC -Wall)
target_compile_options(test PUBLIC -Wall)


# Specify libraries or flags to use when linking a given target 
# and/or its dependents
target_link_libraries(main PUBLIC sensorcmdLib unity)
target_link_libraries(test PUBLIC sensorcmdLib unity)

# Specifies include directories to use when compiling a given target
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/src/unity)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/src/unity)

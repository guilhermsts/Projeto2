# Set CMAKE minimum required version 
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Projeto2)

# Add the sensorLib folder to the build
add_subdirectory(lib)

# Add the executable
add_executable(main main.c)

target_compile_options(main PUBLIC -Wall)

# Generate variables with set of libs and include folders
# Dependencies for libraries files are automatically set 
list(APPEND EXTRA_LIBS sensorcmdLib)
list(APPEND EXTRA_INCLUDES "${CMAKE_SOURCE_DIR}/lib")

# Specify libraries or flags to use when linking a given target 
# and/or its dependents
target_link_libraries(main PUBLIC ${EXTRA_LIBS})

# Specifies include directories to use when compiling a given target
target_include_directories(main PUBLIC ${EXTRA_INCLUDES})

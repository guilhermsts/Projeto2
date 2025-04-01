# Set the source files that make up the library
set(sensorcmd_lib
   cmdproc.h cmdproc.c sensors.c sensors.h unity.c unity.h
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(sensorcmdLib ${LIB_TYPE} ${sensorcmd_lib})

# Set the source files that make up the library
set(cmd_lib
   cmdproc.h cmdproc.c 
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(cmdLib ${LIB_TYPE} ${cmd_lib})
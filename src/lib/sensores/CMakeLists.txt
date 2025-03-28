# Set the source files that make up the library
set(sensor_lib
   sensors.h sensors.c 
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(sensorLib ${LIB_TYPE} ${sensor_lib})
cmake_minimum_required(VERSION 3.5)

project(atlas_scientific_sensors)

# Adding the library
add_library(temp_sensor STATIC
    temp_sensor.cpp 
)
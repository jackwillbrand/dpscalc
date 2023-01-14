cmake_minimum_required(VERSION 3.14)
project(dpscalc)

# Specify the source files
set(SOURCES
    src/dpscalc.cpp
)

# Create an executable
add_executable(dpscalc ${SOURCES})

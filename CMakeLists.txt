cmake_minimum_required(VERSION 3.14)
project(dpscalc)

# Specify the source files
set(SOURCES
    src/dpscalc.cpp
    src/DPSCalculator.cpp
    src/MeleeAttack.cpp
    src/CSVReader.cpp
    src/AttackType.cpp
)

# Create an executable
add_executable(dpscalc ${SOURCES})

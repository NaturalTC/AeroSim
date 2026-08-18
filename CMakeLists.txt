cmake_minimum_required(VERSION 4.1)
project(RadarTech)

set(CMAKE_CXX_STANDARD 20)

add_executable(RadarTech
        src/main.cpp
        src/Aircraft.cpp
        src/Fighter.cpp
        src/PIDController.cpp
        include/Fighter.h
        include/Aircraft.h
        include/PIDController.h
)

target_include_directories(RadarTech PRIVATE include)
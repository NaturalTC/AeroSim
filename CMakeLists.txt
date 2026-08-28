cmake_minimum_required(VERSION 4.1)
project(RadarTech)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR /opt/homebrew/opt/sfml/lib/cmake/SFML)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(RadarTech
        src/main.cpp
        src/Aircraft.cpp
        src/Fighter.cpp
        src/PIDController.cpp
        include/Fighter.h
        include/Aircraft.h
        include/PIDController.h
)

target_include_directories(RadarTech PRIVATE include /opt/homebrew/opt/sfml/include)
target_link_directories(RadarTech PRIVATE /opt/homebrew/opt/sfml/lib)
target_link_libraries(RadarTech SFML::Graphics SFML::Window SFML::System)
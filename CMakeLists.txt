cmake_minimum_required(VERSION 4.2)
project(3d-bin-packing-simulator)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(3d-bin-packing-simulator main.cpp
        main.cpp
        Shape.h
        raygui.h
        Cube.h)

target_link_libraries(3d-bin-packing-simulator PRIVATE raylib)
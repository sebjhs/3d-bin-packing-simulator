cmake_minimum_required(VERSION 4.2)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 23)

add_executable(HelloWorld main.cpp
        Cargo.cpp
        Cargo.h
        CargoCube.cpp
        CargoCube.h
        CargoSphere.cpp
        CargoSphere.h)

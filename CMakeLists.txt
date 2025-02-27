cmake_minimum_required(VERSION 3.29)
project(bd)

set(CMAKE_CXX_STANDARD 20)

add_executable(bd bigdecimal.cpp
        bigdecimal.h
        tests.cpp
)

cmake_minimum_required(VERSION 4.1)
project(cop3003final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cop3003final
        main.cpp
        README.md
        ShiftData.cpp
        ShiftData.h)

cmake_minimum_required(VERSION 3.16)

project(cop3003final)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(cop3003final
        main.cpp
        ShiftData.cpp
        ShiftData.h
        Tracker.cpp
        Tracker.h
        OvertimeShift.cpp
        OvertimeShift.h
)
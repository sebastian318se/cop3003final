cmake_minimum_required(VERSION 3.16)

project(cop3003final)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

# Find the Qt Widgets library for the GUI.
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(.)

add_executable(cop3003final
        main.cpp
        ShiftData.cpp
        ShiftData.h
        Tracker.cpp
        Tracker.h
        TipOut.cpp
        TipOut.h
        PercentTipOut.cpp
        PercentTipOut.h
        FixedTipOut.cpp
        FixedTipOut.h
        Utilities.h
        MainWindow.cpp
        MainWindow.h
)

# Link the Qt Widgets library to our program.
target_link_libraries(cop3003final PRIVATE Qt6::Widgets)


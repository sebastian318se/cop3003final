***COP3003 Final Project – TipTally***

Requirements

C++ compiler supporting C++20

CMake 3.16 or newer

Qt 6 Widgets

rapidcsv library

**Installation**

Install CMake and Qt 6 using Homebrew:

brew install cmake qt

The project also uses rapidcsv for CSV handling. Make sure the rapidcsv header is included in the project.

**Building and Running**

Open a terminal in the project directory.

Configure the project:

cmake -S . -B build

Build the application:

cmake --build build

Run the application:

./build/cop3003final
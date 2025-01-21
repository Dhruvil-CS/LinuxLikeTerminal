cmake_minimum_required(VERSION 3.10)
project(LinuxLikeTerminal)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the "include" directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/shell.cpp
    src/builtins.cpp
    src/utils.cpp
)

# Add executable
add_executable(terminal ${SOURCES})

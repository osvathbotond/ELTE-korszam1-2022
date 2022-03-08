cmake_minimum_required(VERSION 3.21)
project(assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
add_executable(assignment3 src/main.cpp src/LinearFit.cpp src/LinearFit.h src/Linspace.cpp src/Linspace.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

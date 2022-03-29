cmake_minimum_required(VERSION 3.21)
project(assignment4)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
add_executable(assignment4 src/main.cpp src/vector2.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

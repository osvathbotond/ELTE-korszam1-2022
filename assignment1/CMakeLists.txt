cmake_minimum_required(VERSION 3.0.0)
project(hf1 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src)
add_executable(hf1 src/main.cpp src/NewtonIteration.cpp src/NewtonIteration.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.13)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
file(GLOB SRC_FILES source/*.cpp include/*.h)

add_library(Graphs ${SRC_FILES})
add_executable(GraphsTest ${SRC_FILES} mainTest.cpp)
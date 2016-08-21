cmake_minimum_required(VERSION 3.5)
project(MysticSquare)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CPosition.cpp CPosition.h)
add_executable(MysticSquare ${SOURCE_FILES})
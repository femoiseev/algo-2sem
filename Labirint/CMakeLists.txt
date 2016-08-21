cmake_minimum_required(VERSION 3.5)
project(Labirint)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Labirint.cpp Labirint.h)
add_executable(Labirint ${SOURCE_FILES})
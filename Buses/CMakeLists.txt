cmake_minimum_required(VERSION 3.5)
project(Buses)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CSchedule.cpp CSchedule.h)
add_executable(Buses ${SOURCE_FILES})
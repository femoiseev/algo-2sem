cmake_minimum_required(VERSION 3.5)
project(TradeArbitrage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MatrixGraph.cpp MatrixGraph.h)
add_executable(TradeArbitrage ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.3)
project(TreapImplicitKey)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp IImplicitTree.h CImplicitTreap.cpp CImplicitTreap.h CSimpleVector.cpp CSimpleVector.h CTestSequence.cpp CTestSequence.h)
add_executable(TreapImplicitKey ${SOURCE_FILES})
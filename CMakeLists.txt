cmake_minimum_required(VERSION 3.7)
project(cstudy)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp clang/classtest1.cpp clang/myautotest1.cpp cprocess/zombie1.cpp cprocess/fork1.cpp cprocess/daemon1.cpp)
add_executable(cstudy ${SOURCE_FILES})
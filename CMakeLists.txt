cmake_minimum_required(VERSION 3.2)
project(search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(search ${SOURCE_FILES} FoldersMapReduceClient.cpp FoldersMapReduceClient.h)
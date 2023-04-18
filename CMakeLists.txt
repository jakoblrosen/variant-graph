cmake_minimum_required(VERSION 3.24)
project(variant_graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp graph.cpp graph.h node.cpp node.h)

set(CMAKE_BUILD_TYPE Debug)

add_executable(variant_graph ${SOURCE_FILES})

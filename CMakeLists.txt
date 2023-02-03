cmake_minimum_required(VERSION 3.24)
project(variant_graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp graph.cpp graph.h node.cpp node.h)

add_executable(variant_graph ${SOURCE_FILES})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(variant_graph PRIVATE OpenMP::OpenMP_CXX)
endif()

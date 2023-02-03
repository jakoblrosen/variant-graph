cmake_minimum_required(VERSION 3.24)
project(variant_graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(variant_graph main.cpp graph.cpp graph.h node.cpp node.h)

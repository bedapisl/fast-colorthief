cmake_minimum_required(VERSION 2.8.12)
project(fast_colorthief_backend)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

pybind11_add_module(fast_colorthief_backend cpp/fast_colorthief_backend.cpp)

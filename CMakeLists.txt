cmake_minimum_required(VERSION 3.15...3.30)

project(fast_colorthief_backend)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)

#enable_language(CUDA)

#add_library(cuda_fast_colorthief STATIC cpp/kernel.cu)
#set_target_properties(cuda_fast_colorthief PROPERTIES LINKER_LANGUAGE CUDA)
#set_target_properties(cuda_fast_colorthief PROPERTIES CUDA_ARCHITECTURES "50;72")

pybind11_add_module(fast_colorthief_backend cpp/fast_colorthief_backend.cpp)

#target_link_libraries(fast_colorthief_backend PRIVATE cuda_fast_colorthief)
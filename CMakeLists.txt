cmake_minimum_required(VERSION 3.17)
project(d)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mcmodel=large -fopenmp")
add_executable(d test.cpp Matrix.cpp Matrix.h )

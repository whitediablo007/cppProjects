cmake_minimum_required(VERSION 3.20)
project(HW2)

set(CMAKE_CXX_STANDARD 14)

set(EIGEN_DIR "F:/Qt/eigen3")
include_directories(${EIGEN_DIR})

add_executable(HW2
        HW2.cpp)

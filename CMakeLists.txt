cmake_minimum_required(VERSION 3.24)
project(RK2)

set(CMAKE_CXX_STANDARD 17)

add_executable(RK2 main.cpp Data.h tasks_rk2.h tasks_rk2.cpp)

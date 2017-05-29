cmake_minimum_required(VERSION 3.7)
project(MaxClique)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp mis_solver.cpp mis_solver.h ewls.cpp ewls.h numvc.cpp numvc.h)

add_executable(MaxClique ${SOURCE_FILES})
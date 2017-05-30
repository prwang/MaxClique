cmake_minimum_required(VERSION 3.7)
project(MaxClique)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES_SHARED mvc_solver.cpp mvc_solver.h ewls.cpp ewls.h numvc.cpp numvc.h)
set(CMAKE_RELEASE_CXX_FLAGS -Ofast -march=native)
add_executable(MaxClique main.cpp ${SOURCE_FILES_SHARED})
add_executable(PMaxClique main_para.cpp ${SOURCE_FILES_SHARED})
target_link_libraries(PMaxClique pthread boost_thread boost_system)

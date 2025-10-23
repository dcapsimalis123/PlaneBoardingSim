cmake_minimum_required(VERSION 3.10)

project(debug)

add_executable(debug main.cpp Sim.h Sim.cpp Person.h Person.cpp init_types.h init_types.cpp)

target_link_libraries(debug PRIVATE m)
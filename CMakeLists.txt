cmake_minimum_required(VERSION 3.10)

project(debug)

add_executable(debug main.cpp sim.h sim.cpp person.h person.cpp init_types.h init_types.cpp)

target_link_libraries(debug PRIVATE m)
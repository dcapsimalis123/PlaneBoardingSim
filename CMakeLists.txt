cmake_minimum_required(VERSION 3.10)

project(moose)

add_executable(moose main.cpp sim.h sim.cpp person.h person.cpp)

target_link_libraries(moose PRIVATE m)
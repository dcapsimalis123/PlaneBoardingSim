cmake_minimum_required(VERSION 4.1.0)
project(Sim VERSION 0.5)

include_directories(include)
add_library(${PROJECT_NAME} src/BoardingTypes.cpp src/Person.cpp src/Sim.cpp src/InputArguments.cpp)
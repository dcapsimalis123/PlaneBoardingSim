cmake_minimum_required(VERSION 4.1.0)
project(PlaneLoading)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/Sim/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    Sim/src/Person.cpp
    Sim/src/BoardingTypes.cpp
    Sim/src/InputArguments.cpp
    Sim/src/Sim.cpp
)

add_executable(board_debug ${SOURCES})
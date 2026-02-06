cmake_minimum_required(VERSION 4.1.0)
project(board VERSION 0.5) 

include_directories(Sim)
add_subdirectory(Sim)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Sim)
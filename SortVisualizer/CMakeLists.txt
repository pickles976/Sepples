cmake_minimum_required(VERSION 3.5) # specifies version behavior
project(Sort)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
add_executable(Sort main.cpp )
target_link_libraries(Sort SDL2::SDL2)
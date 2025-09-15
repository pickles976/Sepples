cmake_minimum_required(VERSION 3.5) # specifies version behavior
project(Snake)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf CONFIG REQUIRED)
add_executable(Snake main.cpp ./src/colors.hpp ./src/structs.hpp)
target_link_libraries(Snake SDL2::SDL2 SDL2_ttf::SDL2_ttf)
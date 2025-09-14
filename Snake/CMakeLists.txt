cmake_minimum_required(VERSION 3.5) # specifies version behavior
project(Snake)

# Add Snake package
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
add_executable(Snake main.cpp)
target_link_libraries(Snake SDL2::SDL2)
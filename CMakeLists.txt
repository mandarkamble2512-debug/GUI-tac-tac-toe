cmake_minimum_required(VERSION 3.10)
project(TIC)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(TIC main.cpp)
target_link_libraries(TIC sfml-graphics sfml-window sfml-system)
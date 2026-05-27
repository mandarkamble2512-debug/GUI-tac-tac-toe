cmake_minimum_required(VERSION 3.10)
project(TIC)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(TIC main.cpp logic.hpp RenderObjects.hpp)
target_link_libraries(TIC sfml-graphics sfml-window sfml-system)

file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_BINARY_DIR})
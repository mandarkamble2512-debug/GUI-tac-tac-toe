cmake_minimum_required(VERSION 3.10)
project(TIC)

# 1. Find the SFML package
# We specify which modules we need (system, window, graphics, network, audio)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 2. Add your executable
add_executable(TIC main.cpp logic.cpp)


target_link_libraries(TIC sfml-graphics sfml-window sfml-system)
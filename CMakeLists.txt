cmake_minimum_required(VERSION 3.10)
project(TIC)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)

add_executable(TIC main.cpp)

target_link_libraries(TIC PRIVATE ${SFML_LIBRARIES})
target_include_directories(TIC PRIVATE ${SFML_INCLUDE_DIRS})
target_compile_options(TIC PRIVATE ${SFML_CFLAGS_OTHER})

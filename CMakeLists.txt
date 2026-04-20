cmake_minimum_required(VERSION 3.10)
project(PIX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)

add_executable(PIX main.cpp)

target_link_libraries(PIX PRIVATE ${SFML_LIBRARIES})
target_include_directories(PIX PRIVATE ${SFML_INCLUDE_DIRS})
target_compile_options(PIX PRIVATE ${SFML_CFLAGS_OTHER})
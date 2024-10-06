cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(euler LANGUAGES C)

find_package(OpenMP)
find_library(MATH_LIBRARY m)

add_subdirectory(001-050)
add_subdirectory(051-100)

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(euler LANGUAGES C)

find_library(MATH_LIBRARY m REQUIRED)

add_executable(problem-001 problem-001.c)
add_executable(problem-002 problem-002.c)
add_executable(problem-003 problem-003.c)
add_executable(problem-004 problem-004.c)
add_executable(problem-005 problem-005.c)
add_executable(problem-006 problem-006.c)
add_executable(problem-007 problem-007.c)
add_executable(problem-008 problem-008.c)
add_executable(problem-009 problem-009.c)
if(MATH_LIBRARY)
  add_executable(problem-010 problem-010.c)
  target_link_libraries(problem-010 ${MATH_LIBRARY})
endif()

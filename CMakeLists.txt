cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  nonklib
  VERSION 0.0.1
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(tests tests.c)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(benchmarks benches.c)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

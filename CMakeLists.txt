cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  nonklib
  VERSION 0.0.1
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(tests tests.c)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(benchmarks benches.c)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

file(GLOB EXAMPLE_PROGRAMS ${CMAKE_SOURCE_DIR}/examples/*.c)
foreach(EXAMPLE_FILE ${EXAMPLE_PROGRAMS})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
  target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
endforeach()

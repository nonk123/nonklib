cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  nonklib
  VERSION 0.0.1
  LANGUAGES C)

add_executable(tests tests.c)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

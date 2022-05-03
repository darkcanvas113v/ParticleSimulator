cmake_minimum_required(VERSION 3.10)

project(rtmath
  DESCRIPTION "Reinventing the math library"
  VERSION "0.0.1"
)

add_library(rtmath STATIC src/Vector2.cpp)

target_include_directories(rtmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
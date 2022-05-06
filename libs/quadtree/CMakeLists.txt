cmake_minimum_required(VERSION 3.10)

project(quadtree
  DESCRIPTION "Quad tree implementation."
  VERSION "0.0.1"
)

add_library(quadtree STATIC src/quadtree.cpp)

target_include_directories(quadtree
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
cmake_minimum_required(VERSION 3.10)

project(spatialGrid
  DESCRIPTION "Spatial grid implementation."
  VERSION "0.0.1"
)

add_library(spatialGrid STATIC src/spatialGrid.cpp)

target_include_directories(spatialGrid
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(spatialGrid
  PRIVATE rtmath)
cmake_minimum_required(VERSION 3.10)

project(rtGE
  DESCRIPTION "Reinventing the graphic engine."
  VERSION "0.0.1"
)

add_library(rtGE STATIC 
  src/rtGE.cpp
  src/texture_store.cpp
  src/GraphicLayers.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(rtGE
  PRIVATE SDL2 SDL2main SDL2_image SDL2_ttf)

target_include_directories(rtGE
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ParticleSimualtor VERSION 0.0)

add_executable(ParticleSimualtor 
  src/main.cpp 
  src/window.cpp
)

set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include;libs/flecs/include})
set(SDL2_LIBRARIES 
  ${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib;
  ${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib;
  ${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2_image;
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(ParticleSimualtor ${SDL2_LIBRARIES})
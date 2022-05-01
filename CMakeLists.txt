cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ParticleSimulator VERSION 0.0)

add_subdirectory(libs/flecs)

add_executable(ParticleSimulator
  src/main.cpp
  src/window.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(ParticleSimulator
  PRIVATE SDL2 SDL2main SDL2_image
  PRIVATE flecs
)

target_include_directories(ParticleSimulator PUBLIC
  libs/flecs
)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ParticleSimulator VERSION 0.0)

add_subdirectory(libs/flecs)
add_subdirectory(libs/rtmath)

add_executable(ParticleSimulator
  src/main.cpp
  src/game.cpp
  src/utils.cpp

  src/view/window.cpp

  src/logic/CollisionSystem.cpp
  src/logic/MovementSystem.cpp

  src/data/world.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(ParticleSimulator
  PRIVATE SDL2 SDL2main SDL2_image
  PRIVATE flecs
  PRIVATE rtmath
)
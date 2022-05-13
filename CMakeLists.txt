cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

project(ParticleSimulator VERSION 0.0)

add_subdirectory(libs/flecs)
add_subdirectory(libs/rtmath)
add_subdirectory(libs/quadtree)
add_subdirectory(libs/rtGE)
add_subdirectory(libs/spatialGrid)

add_executable(ParticleSimulator
  src/main.cpp
  src/game.cpp
  src/utils.cpp

  src/logic/CollisionSystem.cpp
  src/logic/MovementSystem.cpp
  src/logic/AttractionSystem.cpp

  src/data/world.cpp
)

target_link_libraries(ParticleSimulator
  PRIVATE flecs
  PRIVATE rtmath
  PRIVATE quadtree
  PRIVATE rtGE
  PRIVATE spatialGrid
)
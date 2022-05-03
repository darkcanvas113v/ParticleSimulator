#pragma once
#include <flecs.h>

namespace systems {
  void MovementSystem(flecs::world *w);
  void CollisionSystem(flecs::world *w);
}
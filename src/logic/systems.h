#pragma once
#include <flecs.h>
#include "../data/components/Position.h"
#include "../data/components/Velocity.h"

namespace systems {
  void MovementSystem(flecs::world *w);
  void CollisionSystem(flecs::world *w);
  void AttractionSystem(flecs::world *w);
}
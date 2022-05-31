#pragma once
#include <flecs.h>
#include "../data/components/PositionComponent.h"
#include "../data/components/VelocityComponent.h"
#include "../data/components/SpriteComponent.h"

namespace systems {
  void MovementSystem(flecs::world *w);
  void CollisionSystem(flecs::world *w);
  void AttractionSystem(flecs::world *w);
}
#pragma once
#include <flecs.h>
#include "../data/components/PositionComponent.h"
#include "../data/components/VelocityComponent.h"
#include "../data/components/SpriteComponent.h"

namespace systems {
  void MovementSystem(const flecs::world& w);
  
  void ParticleCollisionSystem(const flecs::world& w);
  void WallCollisionSystem(const flecs::world& w);
  
  void PlanetCollisionSystem(const flecs::world& w);

  void AttractionSystem(const flecs::world& w);
}
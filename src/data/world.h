#pragma once
#include <flecs.h>
#include "components/PositionComponent.h"
#include "components/VelocityComponent.h"
#include "components/RenderComponent.h"
#include "components/SpriteComponent.h"

namespace world {
  void init();

  void clear();
  void destroy();

  void create_particle(
    Vector2 pos,
    Vector2 velocity
  );

  void progress(float dt);

  flecs::query<PositionComponent, RenderComponent, SpriteComponent> get_renderable_entities();

  float get_total_energy();
  
}
#pragma once
#include <flecs.h>
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Render.h"

namespace world {
  void init();

  void clear();
  void destroy();

  void create_particle(
    Vector2 pos,
    Vector2 velocity
  );

  void progress(float dt);

  flecs::query<Position, Render> get_renderable_entities();
  
}
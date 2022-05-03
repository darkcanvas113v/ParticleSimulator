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
    float pos_x,
    float pos_y,
    float vel_x,
    float vel_y
  );

  void progress(float dt);

  flecs::query<Position, Render> get_renderable_entities();
  
}
#include "world.h"

flecs::world mWorld;

void world::init() {
  
}

void world::create_particle(
  float pos_x,
  float pos_y,
  float vel_x,
  float vel_y
) {
  auto e = mWorld.entity()
    .add<Render>()
    .set<Position>({pos_x, pos_y})
    .set<Velocity>({vel_x, vel_y});
}

void world::clear() {
  
}

void world::destroy() {
}

void world::progress(float dt) {
  mWorld.progress(dt);
}

flecs::query<Position, Render> world::get_renderable_entities() {
  return mWorld.query<Position, Render>();
}



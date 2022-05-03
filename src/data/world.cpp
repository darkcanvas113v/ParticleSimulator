#include "world.h"
#include "../logic/systems.h"

flecs::world mWorld;

void world::init() {
  systems::CollisionSystem(&mWorld);
  systems::MovementSystem(&mWorld);
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
  auto all_particles = mWorld.query<>();
  all_particles.each([](flecs::entity e){
    e.destruct();
  });
}

void world::destroy() {
}

void world::progress(float dt) {
  mWorld.progress(dt);
}

flecs::query<Position, Render> world::get_renderable_entities() {
  return mWorld.query<Position, Render>();
}



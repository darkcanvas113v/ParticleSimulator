#include "world.h"
#include "../logic/systems.h"
#include "../utils.h"

flecs::world mWorld;

void world::init() {
  systems::AttractionSystem(&mWorld);
  systems::MovementSystem(&mWorld);
  systems::CollisionSystem(&mWorld);
}

void world::create_particle(
  Vector2 pos,
  Vector2 velocity
) {
  auto e = mWorld.entity()
    .add<Render>()
    .set<Position>({pos})
    .set<Velocity>({velocity});
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



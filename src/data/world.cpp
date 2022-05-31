#include "world.h"
#include "../logic/systems.h"
#include "../utils.h"
#include "rtGE.h"
#include "../view/def.h"

flecs::world mWorld;

void world::init() {
  systems::AttractionSystem(&mWorld);
  systems::MovementSystem(&mWorld);
  systems::CollisionSystem(&mWorld);

  mWorld.entity()
    .add<RenderComponent>()
    .set<PositionComponent>({Vector2 {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}})
    .set<SpriteComponent>({rtGE::get_sprite("circle.png", 300, 300, 150, 150)});
}

void world::create_particle(
  Vector2 pos,
  Vector2 velocity
) {
  auto e = mWorld.entity()
    .add<RenderComponent>()
    .set<PositionComponent>({pos})
    .set<VelocityComponent>({velocity})
    .set<SpriteComponent>({rtGE::get_sprite("circle.png", PARTICLE_SIZE, PARTICLE_SIZE, PARTICLE_RADIUS, PARTICLE_RADIUS)});
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

flecs::query<PositionComponent, RenderComponent, SpriteComponent> world::get_renderable_entities() {
  return mWorld.query<PositionComponent, RenderComponent, SpriteComponent>();
}



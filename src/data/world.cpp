#include "world.h"
#include "../logic/systems.h"
#include "../utils.h"
#include "rtGE.h"
#include "../view/def.h"

flecs::world mWorld;

void world::init() {
  systems::MovementSystem(mWorld);
  // systems::AttractionSystem(mWorld);

  systems::WallCollisionSystem(mWorld);

  systems::PlanetCollisionSystem(mWorld);
  systems::ParticleCollisionSystem(mWorld);
  
  // mWorld.entity()
  //   .add<RenderComponent>()
  //   .set<PositionComponent>({PLANET_POSITION})
  //   .set<SpriteComponent>({rtGE::get_sprite("circle.png", PLANET_SIZE, PLANET_SIZE, PLANET_RADIUS, PLANET_RADIUS)});
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

float world::get_total_energy() {
  auto entities = mWorld.query<VelocityComponent>();

  entities.iter([](flecs::iter& iter, VelocityComponent* v) {
    float total_energy = 0;
    for (int i : iter) {
      auto velocity = v[i].vec.length();
      total_energy += velocity * velocity / 2;
    }

    return total_energy;
  });
}


#include "systems.h"
#include "../view/def.h"

const float G = 30000;
const float ELECTRIC_ATTRACTION = 10000.0;

void systems::AttractionSystem(const flecs::world& w) {
  w.system<PositionComponent, VelocityComponent>()
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
      for (int i = 0; i < iter.count(); i++) {
        Vector2 vec = PLANET_POSITION - p[i].current;
        float distSqrd = vec.length();
        v[i].vec = v[i].vec + G / distSqrd * iter.delta_time() * vec.normalized();
      }
   });
}
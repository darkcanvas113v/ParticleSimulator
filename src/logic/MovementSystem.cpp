#include "systems.h"
#include <spatialGrid.h>

void systems::MovementSystem(const flecs::world& w) {
  w.system<PositionComponent, VelocityComponent>()
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
      spatialGrid::reset();
      for (int i : iter) {
        auto e = iter.entity(i);
        auto pp = p[i].current;
        spatialGrid::insert(Entity {pp.x, pp.y, e.raw_id()});

        p[i].movement_vec = v[i].vec * iter.delta_time();
        
        p[i].future = p[i].current + p[i].movement_vec;
      }
   });

  w.system<PositionComponent, VelocityComponent>()
   .kind(flecs::PostUpdate)
   .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
     for (int i : iter) {
       p[i].current = p[i].future;
     }
   });
}
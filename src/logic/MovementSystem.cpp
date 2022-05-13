#include "systems.h"
#include <spatialGrid.h>

void systems::MovementSystem(flecs::world *w) {
  w->system<Position, Velocity>()
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& iter, Position* p, Velocity* v) {
      spatialGrid::reset();
      for (int i : iter) {
        auto e = iter.entity(i);
        auto pp = p[i].current;
        spatialGrid::insert(Entity {pp.x, pp.y, e.raw_id()});

        p[i].movement_vec = v[i].vec * iter.delta_time();
        
        p[i].future = p[i].current + p[i].movement_vec;
      }
   });

  w->system<Position, Velocity>()
   .kind(flecs::PostUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       p[i].current = p[i].future;
     }
   });
}
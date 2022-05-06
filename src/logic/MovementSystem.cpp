#include "systems.h"
#include <quadtree.h>

void systems::MovementSystem(flecs::world *w) {
  w->system<Position, Velocity>()
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& iter, Position* p, Velocity* v) {
      quad_tree::reset();
      for (int i : iter) {
        auto e = iter.entity(i);
        quad_tree::insert(Entity {p[i].current.x, p[i].current.y, e.raw_id()});
        
        p[i].movement_vec = v[i].vec * iter.delta_time();

        p[i].future = p[i].current + p[i].movement_vec;
      }
      quad_tree::build();
   });

  w->system<Position, Velocity>()
   .kind(flecs::PostUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       p[i].current = p[i].future;
     }
   });
}
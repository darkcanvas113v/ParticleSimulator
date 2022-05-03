#include "systems.h"
#include "../data/components/Position.h"
#include "../data/components/Velocity.h"

void systems::MovementSystem(flecs::world *w) {
  w->system<Position, Velocity>()
    .kind(flecs::PreUpdate)
    .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       p[i].future_x = p[i].x + v[i].x * iter.delta_time();
       p[i].future_y = p[i].y + v[i].y * iter.delta_time();
     }
   });

  w->system<Position, Velocity>()
   .kind(flecs::PostUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       p[i].x = p[i].future_x;
       p[i].y = p[i].future_y;
     }
   });
}
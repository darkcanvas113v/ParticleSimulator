#include "systems.h"
#include "../data/components/Position.h"
#include "../data/components/Velocity.h"
#include "../view/def.h"
#include <stdio.h>

void systems::CollisionSystem(flecs::world *w) {
  w->system<Position, Velocity>()
   .kind(flecs::OnUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       if (p[i].future_x < PARTICLE_RADIUS) {
         v[i].x = -v[i].x;
         p[i].future_x = -p[i].future_x + 2*PARTICLE_RADIUS;
       }
       else if (p[i].future_x > SCREEN_WIDTH - PARTICLE_RADIUS) {
         v[i].x = -v[i].x;
         p[i].future_x = 2*SCREEN_WIDTH - p[i].future_x - 2*PARTICLE_RADIUS;
       }

       if (p[i].future_y < PARTICLE_RADIUS) {
         v[i].y = -v[i].y;
         p[i].future_y = -p[i].future_y + 2*PARTICLE_RADIUS;
       }
       else if (p[i].future_y > SCREEN_HEIGHT - PARTICLE_RADIUS) {
         v[i].y = -v[i].y;
         p[i].future_y = 2*SCREEN_HEIGHT - p[i].future_y - 2*PARTICLE_RADIUS;
       }
     }
   });
}
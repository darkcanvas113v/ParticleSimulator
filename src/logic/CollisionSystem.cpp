#include "systems.h"
#include "../view/def.h"
#include <stdio.h>

void systems::CollisionSystem(flecs::world *w) {
  w->system<Position, Velocity>()
   .kind(flecs::OnUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     for (int i : iter) {
       if (p[i].future.x < PARTICLE_RADIUS) {
         v[i].vec.x = -v[i].vec.x;
         p[i].future.x = -p[i].future.x + 2*PARTICLE_RADIUS;
       }
       else if (p[i].future.x > SCREEN_WIDTH - PARTICLE_RADIUS) {
         v[i].vec.x = -v[i].vec.x;
         p[i].future.x = 2*SCREEN_WIDTH - p[i].future.x - 2*PARTICLE_RADIUS;
       }

       if (p[i].future.y < PARTICLE_RADIUS) {
         v[i].vec.y = -v[i].vec.y;
         p[i].future.y = -p[i].future.y + 2*PARTICLE_RADIUS;
       }
       else if (p[i].future.y > SCREEN_HEIGHT - PARTICLE_RADIUS) {
         v[i].vec.y = -v[i].vec.y;
         p[i].future.y = 2*SCREEN_HEIGHT - p[i].future.y - 2*PARTICLE_RADIUS;
       }
     }
   });

  //  w->system<Position, Velocity>()
  //  .kind(flecs::OnUpdate)
  //  .iter([](flecs::iter& iter, Position* p, Velocity* v) {
  //    for (int i = 0; i < iter.count(); i++) {
  //      for (int j = i; j < iter.count(); j++) {
  //        float distSqrd = p[i].current.distSqrd(p[j].current);

  //        Vector2 movementVec = p[i].movement_vec - p[j].movement_vec;
  //        float sumRadii = 2*PARTICLE_RADIUS;

  //      }
  //    }
  //  });
}
#include "systems.h"
#include "../view/def.h"
#include <stdio.h>
#include <math.h>

void systems::WallCollisionSystem(const flecs::world& w) {
  w.system<PositionComponent, VelocityComponent>()
   .kind(flecs::OnUpdate)
   .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
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
}
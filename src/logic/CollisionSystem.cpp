#include "systems.h"
#include "../view/def.h"
#include <stdio.h>
#include <math.h>
#include <spatialGrid.h>

// Collision detectinon
void systems::CollisionSystem(flecs::world *w) {
  w->system<PositionComponent, VelocityComponent>()
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

   w->system<PositionComponent, VelocityComponent>()
   .kind(flecs::OnUpdate)
   .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
     // Collision detection between particles, source: https://www.gamedeveloper.com/programming/pool-hall-lessons-fast-accurate-collision-detection-between-circles-or-spheres
     for (int i = 0; i < iter.count(); i++) {
       PositionComponent p1 = p[i];
       VelocityComponent v1 = v[i];

       auto entities = spatialGrid::get_childrens_around(p1.current.x, p1.current.y, PARTICLE_RADIUS, p1.movement_vec.x, p1.movement_vec.y);
       for (auto e = entities.start; e != entities.end; e++) {
         auto entity = flecs::entity(iter.world(), e->id);

         if (iter.entity(i).raw_id() == e->id) {
           continue;
         }

         PositionComponent p2 = *entity.get<PositionComponent>();
         VelocityComponent v2 = *entity.get<VelocityComponent>();

         float d = p1.current.dist(p2.current);

         Vector2 movementVec = p1.movement_vec - p2.movement_vec;
         float sumRadii = (2*PARTICLE_RADIUS);

         if (movementVec.length() < d - sumRadii) continue;

         Vector2 moveVectorNorm = movementVec.normalized();

         Vector2 C = p2.current - p1.current;
         float D = moveVectorNorm.dot(C);

         if (D <= 0) continue;
         float sumRadiiSqrd = sumRadii * sumRadii;

         float F = C.lengthSqrd() - D * D;
         if (F >= sumRadiiSqrd) continue;

         float T = sumRadiiSqrd - F;
         if (T < 0) continue;

         float dist = D - sqrt(T);
         float mag = movementVec.length();

         if (mag < dist) continue;

         float ratio = dist / mag;

         float m1 = 1;
         float m2 = 1;

         Vector2 posOnImpact1 = p1.current + p1.movement_vec * ratio;
         Vector2 posOnImpact2 = p2.current + p2.movement_vec * ratio;

        //  Vector2 movement_vec_on_impact1 = p[i].movement_vec * (1 - ratio);
        //  Vector2 movement_vec_on_impact2 = p[j].movement_vec * (1 - ratio);

         Vector2 n = (posOnImpact2 - posOnImpact1).normalized();
         float a1 = v1.vec.dot(n);
         float a2 = v2.vec.dot(n);

         float P = (2.0 * (a1 - a2)) / (m1 + m2);

         v[i].vec = v1.vec - n * P * m2;
         entity.set<VelocityComponent>({v2.vec + n * P * m2});

         p[i].future = posOnImpact1 + v[i].vec * iter.delta_time() * (1 - ratio);
         
         Vector2 movement_vector2 = v2.vec * iter.delta_time() * (1 - ratio);
         entity.set<PositionComponent>({p2.current, posOnImpact2 + movement_vector2, movement_vector2});
       }
     }
   });
}
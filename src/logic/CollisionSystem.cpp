#include "systems.h"
#include "../view/def.h"
#include <stdio.h>
#include <math.h>
#include <quadtree.h>

Rect get_danger_area(Position& p) {
  float r = PARTICLE_RADIUS * 2;
  Vector2 v = p.movement_vec;
  float xs = signbit(v.x);
  float ys = signbit(v.y);
  return Rect {p.current.x - r + xs * v.x, p.current.y - r + ys, r * 2 + abs(v.x), r * 2 + abs(v.y)};
}

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

   w->system<Position, Velocity>()
   .kind(flecs::OnUpdate)
   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
     // Collision detection between particles, source: https://www.gamedeveloper.com/programming/pool-hall-lessons-fast-accurate-collision-detection-between-circles-or-spheres
     for (int i = 0; i < iter.count(); i++) {
       auto close_entities = quad_tree::get_childrens_at(get_danger_area(p[i]));

       int processed_collisions = 0;

       for (Entity* e = close_entities.start; e != close_entities.end; e++) {
         auto entity = flecs::entity(iter.world(), e->id);

         if (iter.entity(i).raw_id() == e->id) {
           continue;
         }

         Position p1 = p[i];
         Position p2 = *entity.get<Position>();

         Velocity v1 = v[i];
         Velocity v2 = *entity.get<Velocity>();

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
         v2.vec = v2.vec + n * P * m2;
         entity.set<Velocity>({v2.vec});

         p[i].movement_vec = v[i].vec * iter.delta_time() * (1 - ratio);
         p[i].future = posOnImpact1 + p[i].movement_vec;

         Vector2 movement_vector2 = v2.vec * iter.delta_time() * (1 - ratio);
         entity.set<Position>({p2.current, posOnImpact2 + movement_vector2, movement_vector2});

         if (++processed_collisions > 2) break;
       }
     }
   });
}
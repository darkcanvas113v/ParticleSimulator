#include "systems.h"
#include "../view/def.h"
#include <stdio.h>
#include <math.h>

void systems::PlanetCollisionSystem(const flecs::world& w) {
  w.system<PositionComponent, VelocityComponent>()
  .kind(flecs::OnUpdate)
  .iter([](flecs::iter& iter, PositionComponent* p, VelocityComponent* v) {
    for (int i : iter) {
      Vector2 C = PLANET_POSITION - p[i].current;
      float d = C.length();

      auto movementVec = p[i].movement_vec;

      if (movementVec.length() < d - PLAN_PART_RADIUS_SUM) continue;

      Vector2 moveVectorNorm = movementVec.normalized();

      float D = moveVectorNorm.dot(C);

      if (D <= 0) continue;

      float F = C.lengthSqrd() - D * D;
      if (F >= PLAN_PART_RADIUS_SUM_SQRD) continue;

      float T = PLAN_PART_RADIUS_SUM_SQRD - F;
      if (T < 0) continue;

      float dist = D - sqrt(T);
      float mag = movementVec.length();

      if (mag < dist) continue;

      float ratio = dist / mag;

      Vector2 posOnImpact = p[i].current + p[i].movement_vec * ratio;

      Vector2 n = (PLANET_POSITION - posOnImpact).normalized();
      float a1 = v[i].vec.dot(n);
      float P = (2.0 * a1);

      v[i].vec = v[i].vec - n * P;
     }
   });
}
#include "systems.h"

const Vector2 gravity = Vector2 {0, 9.8};
const float ELECTRIC_ATTRACTION = 10000.0;

void systems::AttractionSystem(const flecs::world& w) {
  // w->system<Position, Velocity>()
  //   .kind(flecs::PreUpdate)
  //   .iter([](flecs::iter& iter, Position* p, Velocity* v) {
  //     for (int i = 0; i < iter.count(); i++) {
  //       // v[i].vec = v[i].vec + gravity * iter.delta_time();
        
  //       for (int j = i + 1; j < iter.count(); j++) {
  //         auto vec = p[j].current - p[i].current;

  //         float dist = vec.length();
  //         float magnitude = ELECTRIC_ATTRACTION / (dist * dist);

  //         auto force = vec.normalized() * magnitude;
  //         v[i].vec = v[i].vec + force * iter.delta_time();
  //         v[j].vec = v[j].vec - force * iter.delta_time();
  //       }
  //     }
  //  });
}
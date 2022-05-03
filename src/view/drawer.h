#pragma once
#include <flecs.h>
#include "../data/components/Position.h"
#include "../data/components/Render.h"

namespace drawer {
  void draw(flecs::query<Position, Render> renderables);
}
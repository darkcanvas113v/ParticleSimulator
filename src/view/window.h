#pragma once

#include <SDL2/SDL.h>

namespace window {
  bool init();

  void draw();

  void update();

  void close();

  void draw_circle(
    float pos_x,
    float pos_y
  );
}


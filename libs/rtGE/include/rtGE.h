#pragma once

namespace rtGE {
  bool init(int screenWidth, int screenHeight, char* label);

  void draw();

  void draw_text(float x, float y, char* text);

  void update();

  void close();

  void draw_circle(
    float pos_x,
    float pos_y,
    float D
  );
}
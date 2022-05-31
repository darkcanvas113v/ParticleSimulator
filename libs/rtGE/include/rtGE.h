#pragma once
#include <string>

class Sprite {
public:
  int texture_id;
  int w, h;

  Sprite(int texture_id, float w, float h) {
    this->texture_id = texture_id;

    this->w = w;
    this->h = h;
  }
};

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

  void draw_sprite(const Sprite* sprite, float x, float y);

  Sprite* get_sprite(std::string name, float w, float h);

  void load_texture(std::string name);
}
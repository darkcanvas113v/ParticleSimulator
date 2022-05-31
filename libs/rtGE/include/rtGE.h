#pragma once
#include <string>

class Sprite {
public:
  int texture_id;
  int w, h;
  int origin_x, origin_y;

  Sprite(int texture_id, float w, float h, float origin_x = 0, float origin_y = 0) {
    this->texture_id = texture_id;

    this->origin_x = origin_x;
    this->origin_y = origin_y;

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

  Sprite* get_sprite(std::string name, float w, float h, float origin_x = 0, float origin_y = 0);

  void load_texture(std::string name);
}
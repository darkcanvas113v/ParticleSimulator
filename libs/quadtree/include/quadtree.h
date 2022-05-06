#pragma once

struct Entity {
  float x, y;
  unsigned long id;

  float loc_x, loc_y;
  int quad_id;
};

struct EntityIterator {
  Entity* start;
  Entity* end;
  int size = end - start;
};

struct Rect {
  float x, y, w, h;

  bool overlaps(const Rect r) {
    return (x < r.x + r.w && x + w > r.x && y < r.y + r.h && y + h > r.y);
  }
};

namespace quad_tree {
  void init_quad(float x, float y, float w);

  void reset();

  void insert(const Entity& entity);

  void build();

  EntityIterator get_childrens_at(Rect r);
}

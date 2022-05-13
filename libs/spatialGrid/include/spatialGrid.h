#pragma once

struct Entity {
  float x, y;
  unsigned long id;
};

struct EntityIterator {
  Entity* start;
  Entity* end;
  int size = end - start;
};


namespace spatialGrid {
  void init(float w, float h, float argGridSize, int maxCapacity);

  void reset();

  void insert(Entity entity);

  EntityIterator get_childrens_around(float x, float y, float radius);
}

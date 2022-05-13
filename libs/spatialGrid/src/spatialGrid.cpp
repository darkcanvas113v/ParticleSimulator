#include "../include/spatialGrid.h"
#include "rtmath.h"

float gridSize;
const int GRID_CAPACITY = 10;

struct Grid {
  Entity* entities;
  int size = 0;

  void init(int capacity) {
    entities = new Entity[capacity];
    size = 0;
  }

  void reset() {
    size = 0;
  }

  void insert(Entity& e) {
    entities[size++] = e;
  }
};

int rows, columns;
Grid* table;

const int BUFFER_SIZE = 100;
int buffer_i;
Entity buffer[BUFFER_SIZE];

void spatialGrid::init(float w, float h, float argGridSize, int maxCapacity) {
  gridSize = argGridSize;

  rows = round_up(h / gridSize);
  columns = round_up(w / gridSize);
  table = new Grid[rows * columns];

  for (int i = 0; i < rows*columns; i++) {
    table[i].init(maxCapacity);
  }
}

void spatialGrid::reset() {
  for (int i = 0; i < rows*columns; i++) {
    table[i].reset();
  }
}

void spatialGrid::insert(Entity entity) {
  int grid_pos_x = entity.x / gridSize;
  int grid_pos_y = entity.y / gridSize;

  table[grid_pos_y * columns + grid_pos_x].insert(entity);
}

EntityIterator spatialGrid::get_childrens_around(float x, float y, float radius) {
  buffer_i = 0;

  int left_corner_x = cap_low((x - radius) / gridSize, 0);
  int left_corner_y = cap_low((y - radius) / gridSize, 0);

  int right_corner_x = cap_up((x + radius) / gridSize, columns - 1);
  int right_corner_y = cap_up((y + radius) / gridSize, rows - 1);

  for (int i = left_corner_x; i < right_corner_x + 1; i++) {
    for (int j = left_corner_y; j < right_corner_y + 1; j++) {
      auto grid = table[j*columns + i];

      for (int k = 0; k < grid.size; k++) {
        buffer[buffer_i++] = grid.entities[k];
      }
    }
  }
  return EntityIterator { buffer, buffer + buffer_i };
}
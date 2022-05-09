#include "../include/spatialGrid.h"
#include "rtmath.h"

const int GRID_SIZE = 50;
const int GRID_RADIUS = GRID_SIZE / 2;
const int GRID_CAPACITY = 10;

struct Grid {
  Entity entities[GRID_CAPACITY];
  int size = 0;

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

void spatialGrid::init(float w, float h) {
  rows = round_up(h / GRID_SIZE);
  columns = round_up(w / GRID_SIZE);
  table = new Grid[rows * columns];
}

void spatialGrid::reset() {
  for (int i = 0; i < rows*columns; i++) {
    table[i].reset();
  }
}

void spatialGrid::insert(Entity entity) {
  int grid_pos_x = entity.x / GRID_SIZE;
  int grid_pos_y = entity.y / GRID_SIZE;

  table[grid_pos_y * columns + grid_pos_x].insert(entity);
}

EntityIterator spatialGrid::get_childrens_around(float x, float y, float radius) {
  buffer_i = 0;

  int left_corner_x = round_up((x - radius) / GRID_SIZE);
  int left_corner_y = round_up((y - radius) / GRID_SIZE);

  int right_corner_x = round_up((x + radius) / GRID_SIZE);
  int right_corner_y = round_up((y + radius) / GRID_SIZE);

  for (int i = left_corner_x; i < right_corner_x; i++) {
    for (int j = left_corner_y; j < right_corner_y; j++) {
      auto grid = table[j*columns + i];

      for (int k = 0; k < grid.size; k++) {
        buffer[buffer_i++] = grid.entities[k];
      }
    }
  }
  return EntityIterator { buffer, buffer + buffer_i };
}
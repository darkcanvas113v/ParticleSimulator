#pragma once
#include "../include/quadtree.h"

const int MAX_CHILDREN = 5;

struct Position
{
  float x, y;
};


struct Quad
{
  Entity childrens[MAX_CHILDREN];
  float x, y, w;
  int count;

  bool divided = false;

  Quad* quads[4];

  Rect rect;

  void add_childrens_at_to_buffer(Rect r);
  Quad() {}
  Quad(float x, float y, float w);
  void insert(EntityIterator entities);
};
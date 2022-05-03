#pragma once
#include <rtmath.h>

struct Position {
  Vector2 current;
  Vector2 future;
  Vector2 movement_vec;
};
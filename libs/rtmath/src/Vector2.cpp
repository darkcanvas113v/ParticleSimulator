#include "../include/rtmath.h"
#include <math.h>

Vector2 Vector2::operator+(const Vector2& vec) {
  return Vector2 {x + vec.x, y + vec.y};
}

Vector2 Vector2::operator-(const Vector2& vec) {
  return Vector2 {x - vec.x, y - vec.y};
}

Vector2 Vector2::operator*(float n) {
  return Vector2 {x * n, y * n};
}

void Vector2::operator=(const Vector2& vec) {
  x = vec.x;
  y = vec.y;
}

float Vector2::distSqrd(const Vector2& vec) {
  return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y);
}

float Vector2::lengthSqrd() {
  return x*x + y*y;
}

float Vector2::length() {
  return sqrt(lengthSqrd());
}

Vector2 Vector2::normalized() {
  float l = length();
  return {x / l, y / l};
}
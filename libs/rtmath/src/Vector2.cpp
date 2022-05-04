#include "../include/rtmath.h"
#include <math.h>

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
  return Vector2 {v1.x + v2.x, v1.y + v2.y};
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
  return Vector2 {v1.x - v2.x, v1.y - v2.y};
}

Vector2 operator*(const Vector2& v1, float n) {
  return Vector2 {v1.x * n, v1.y * n};
}

Vector2 operator*(float n, const Vector2& v1) {
  return Vector2 {v1.x * n, v1.y * n};
}

void Vector2::operator=(const Vector2& vec) {
  x = vec.x;
  y = vec.y;
}

float Vector2::distSqrd(const Vector2& vec) {
  return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y);
}

float Vector2::dist(const Vector2& vec) {
  return sqrt(distSqrd(vec));
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

float Vector2::dot(const Vector2& vec) {
  return x * vec.x + y * vec.y;
}
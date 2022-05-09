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
  float inv_sqrt = fast_sqrt(lengthSqrd());
  return {x *inv_sqrt, y *inv_sqrt};
}

float Vector2::dot(const Vector2& vec) {
  return x * vec.x + y * vec.y;
}

float fast_sqrt(float val) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = val * 0.5F;
    y = val;

    i = * (long*) &y;
    i = 0x5F375A86 - (i >> 1);
    y = * (float*) &i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
}
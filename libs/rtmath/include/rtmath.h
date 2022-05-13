#pragma once

struct Vector2 {
    float x, y;

    // Vector2 operator+(const Vector2& v1, const Vector2& v2);
    // Vector2 operator-(const Vector2& v1, const Vector2& v2);
    // Vector2 operator-(const Vector2& vec);
    // Vector2 operator*(float n);
    void operator=(const Vector2&);

    float distSqrd(const Vector2& vec);
    float dist(const Vector2& vec);
    float lengthSqrd();
    float length();
    Vector2 normalized();

    float dot(const Vector2& vec);
};

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v1, float n);
Vector2 operator*(float n, const Vector2& v1);

float fast_sqrt(float val);

int round_up(float);

int cap_low(int, int);
int cap_up(int, int);
#pragma once

struct Vector2 {
    float x, y;

    Vector2 operator+(const Vector2& vec);
    Vector2 operator-(const Vector2& vec);
    Vector2 operator*(float n);
    void operator=(const Vector2&);

    float distSqrd(const Vector2& vec);
    float lengthSqrd();
    float length();
    Vector2 normalized();

    float dot(const Vector2& vec);
};
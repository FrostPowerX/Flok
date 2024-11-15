#pragma once

#include "raylib.h"

namespace Math {

float GetRotation(const Vector2& A);

Vector2 Rotate(const Vector2& A, float Angle);

Vector2 Subtract(const Vector2& A, const Vector2& B);

Vector2 Add(const Vector2& A, const Vector2& B);

Vector2 Normalize(const Vector2& A, float Mag);

Vector2 Multiply(const Vector2& A, float K);

float GetMag(const Vector2& A);

bool IsEqual(const Vector2& A, const Vector2& B);

bool IsEqual(float A, float B);

bool IsInRect(const Rectangle& Rect, Vector2 Pos);
} // namespace Math

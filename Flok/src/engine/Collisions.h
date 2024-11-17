#pragma once

#include "raylib.h"

namespace Collisions {

enum class WhereCollides {
  Up,
  Down,
  Left,
  Right
};

bool IsCircleCircle(const Vector2& APosition, float ARadius, const Vector2& BPosition, float BRadius);

bool IsBorderCircle(const Vector2& Position, float Radius, WhereCollides& CollisionPlace);

bool IsDotBorder(const Vector2& Position, WhereCollides& CollisionPlace);

bool IsRectRect(const Rectangle& A, const Rectangle& B);

bool IsRectBorder(const Rectangle& A);

bool IsRectMouse(const Rectangle& A);

}

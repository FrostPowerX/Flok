﻿#include "Collisions.h"

#include <iostream>

#include "Constants.h"

namespace Collisions {

bool IsCircleCircle(const Vector2& APosition, const float ARadius, const Vector2& BPosition, const float BRadius) {

  const float k_Dist = (APosition.x - BPosition.x) * (APosition.x - BPosition.x) +
                       (APosition.y - BPosition.y) * (APosition.y - BPosition.y);

  const float k_Radii = (ARadius + BRadius) * (ARadius + BRadius);

  // Sum(Radius)^2 >= Dist^2
  // saves the necessity of a sqrt
  return k_Radii >= k_Dist;
}

bool IsBorderCircle(const Vector2& Position, const float Radius, WhereCollides& CollisionPlace) {

  bool Collides = false;

  if (Position.x + Radius >= g_ScreenWidth) {
    Collides = true;
    CollisionPlace = WhereCollides::Right;

  } else if (Position.x - Radius <= 0) {
    Collides = true;
    CollisionPlace = WhereCollides::Left;

  } else if (Position.y - Radius <= 0) {
    Collides = true;
    CollisionPlace = WhereCollides::Up;

  } else if (Position.y + Radius >= g_ScreenHeight) {
    Collides = true;
    CollisionPlace = WhereCollides::Down;
  }
  return Collides;
}

bool IsDotBorder(const Vector2& Position, WhereCollides& CollisionPlace) {

  bool Collides = false;

  if (Position.x >= g_ScreenWidth) {
    Collides = true;
    CollisionPlace = WhereCollides::Right;

  } else if (Position.x <= 0) {
    Collides = true;
    CollisionPlace = WhereCollides::Left;

  } else if (Position.y >= g_ScreenHeight) {
    Collides = true;
    CollisionPlace = WhereCollides::Down;

  } else if (Position.y <= 0) {
    Collides = true;
    CollisionPlace = WhereCollides::Up;
  }

  return Collides;
}

bool IsRectRect(const Rectangle& A, const Rectangle& B) {

  if ((A.x + A.width >= B.x && A.x <= B.x + B.width)) {
    if ((A.y + A.height >= B.y && A.y <= B.y + B.height)) {
      return true;
    }
  }

  return false;
}

bool IsRectBorder(const Rectangle& A) {

  return A.x <= 0 || A.x + A.width >= static_cast<float>(g_ScreenWidth) || A.y <= 0 ||
         A.y + A.height >= static_cast<float>(g_ScreenHeight);
}

bool IsRectMouse(const Rectangle& A) {

  if ((GetMousePosition().x >= A.x && GetMousePosition().x <= A.x + A.width)) {
    if ((GetMousePosition().y >= A.y && GetMousePosition().y <= A.y + A.height)) {
      return true;
    }
  }

  return false;
}

} // namespace Collisions

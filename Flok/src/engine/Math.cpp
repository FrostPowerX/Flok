#include "Math.h"

#include <cfloat>
#include <cmath>
#include <iostream>

using namespace std;

namespace Math {

using Rads = float;

float RadianCast(const Rads Degree) {

  return Degree * 180.0F / PI;
}

float GetRotation(const Vector2& A) {

  int Quad = 0;
  Rads Degree = 0;

  if (A.x >= 0) {
    if (A.y <= 0) {
      Quad = 1;
    } else {
      Quad = 4;
    }

  } else {
    if (A.y <= 0) {
      Quad = 2;
    } else {
      Quad = 3;
    }
  }

  switch (Quad) {
    case 1:
      Degree = atan(-A.y / A.x);
      break;

    case 3:
      Degree = PI + atan(-A.y / A.x);
      break;

    case 4:
      Degree = 2 * PI + atan(-A.y / A.x);
      break;

    default:
      cerr << "Err Math.cpp:54"
           << "\n";
      break;
  }

  return RadianCast(Degree);
}

Vector2 Rotate(const Vector2& A, float Angle) {

  float OgAngle = atan(-A.y / A.x);

  if (A.x < 0) {
    OgAngle = PI + OgAngle;
  } else if (A.x >= 0 && A.y > 0) {
    OgAngle = 2.0F * PI + OgAngle;
  }

  if (Angle > 2.0F * PI) {
    Angle = Angle * PI / 180.0F;
  }

  OgAngle += Angle;

  // rotation Matrix
  return {A.x * cos(OgAngle) - A.y * sin(OgAngle), A.x * sin(OgAngle) + A.y * cos(OgAngle)};
}

Vector2 Subtract(const Vector2& A, const Vector2& B) {

  return {(A.x - B.x), (A.y - B.y)};
}

Vector2 Add(const Vector2& A, const Vector2& B) {

  return {(B.x + A.x), (B.y + A.y)};
}

Vector2 Normalize(const Vector2& A, const float Mag) {

  return {A.x / Mag, A.y / Mag};
}

Vector2 Multiply(const Vector2& A, const float K) {

  return {A.x * K, A.y * K};
}

float GetMag(const Vector2& A) {

  return sqrtf(powf(A.x, 2) + powf(A.y, 2));
}

bool IsEqual(const Vector2& A, const Vector2& B) {

  return IsEqual(A.x, B.x) && IsEqual(A.y, B.y);
}

bool IsEqual(const float A, const float B) {

  return A >= B - FLT_EPSILON && A <= B + FLT_EPSILON;
}

bool IsInRect(const Rectangle& Rect, const Vector2 Pos) {

  return Pos.x > Rect.x && Pos.x <= Rect.width + Rect.x && Pos.y > Rect.y && Pos.y < Rect.y + Rect.height;
}

} // namespace Math

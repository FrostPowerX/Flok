#pragma once
#include <raylib.h>

namespace PlayerClass {
struct PlayerType {
  Rectangle f_BoundingBox;
  Vector2 f_Direction;
  float f_Speed;
  //Texture2D f_Sprite;
};

void Init();
void Push(const Vector2& Direction, float Force);
void Update();
void Draw();

};

#pragma once
#include <raylib.h>

namespace PlayerClass {
struct PlayerType {
  Rectangle f_BoundingBox;
  Vector2 f_Direction;
  float f_Speed;
  float f_FrameTimer;
  float f_Frame;
  Texture2D f_Sprite;
};



void Init();

void Unload();

void Push(const Vector2& Direction, float Force);

void Update();

void Draw();

Rectangle GetBoundingBox();

void SetPosition(int x, int y);

void MovePlayer(float Height);

float GetSpeed();
};

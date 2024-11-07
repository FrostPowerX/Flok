#pragma once

namespace Wall {
struct WallType {
  float f_Position;
  float f_GapStart;
  float f_GapSize;
  float f_Speed;
  bool f_IsHidden;
  int f_UniqueId;
  float f_WallWidth;
};



WallType Make(float Speed);

void Reset(WallType& Wall, float Speed);

void Update(WallType& Wall);

void Draw(const WallType& Wall);
};

#pragma once

#include "raylib.h"

namespace Actors {

struct WallType {
  Texture2D f_Sprite;

  float f_Position;
  float f_GapStart;
  float f_GapSize;
  float f_Speed;
  float f_WallWidth;

  int f_UniqueId;

  bool f_IsHidden;
  bool f_checked;
};

WallType MakeWall(float Speed);

void ResetWall(WallType& Wall, float Speed);

void UpdateWalls(WallType& Wall);

void DrawWalls(const WallType& Wall);

} // namespace Actors

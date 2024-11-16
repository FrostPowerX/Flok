#pragma once

namespace Actors {

struct WallType {
  float f_Position;
  float f_GapStart;
  float f_GapSize;
  float f_Speed;
  bool f_IsHidden;
  int f_UniqueId;
  float f_WallWidth;
};

WallType MakeWall(float Speed);

void ResetWall(WallType& Wall, float Speed);

void UpdateWalls(WallType& Wall);

void DrawWalls(const WallType& Wall);

}

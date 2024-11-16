#include "WallClass.h"

#include "raylib.h"

#include "Constants.h"

namespace Actors {

constexpr float k_WallWidth = 50;
constexpr int k_MaxGapH = 300;

// TODO
//  Replace with player width
constexpr int k_MinGapH = 120;

int UniqueId = 0;

float GetRandomGapStart() {

  return static_cast<float>(GetRandomValue(0, g_ScreenHeight - k_MaxGapH));

}

float GetRandomGapHeight() {

  return static_cast<float>(GetRandomValue(k_MinGapH, k_MaxGapH));

}

WallType MakeWall(const float Speed) {

  return {.f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_IsHidden = true,
          .f_UniqueId = UniqueId++,
          .f_WallWidth = k_WallWidth};

}

void ResetWall(WallType& Wall, const float Speed) {

  Wall = {.f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_IsHidden = true,
          .f_UniqueId = Wall.f_UniqueId,
          .f_WallWidth = k_WallWidth};

}

void UpdateWalls(WallType& Wall) {

  Wall.f_Position -= Wall.f_Speed * GetFrameTime();

}

void DrawWalls(const WallType& Wall) {

  // Change to draw Texture
  DrawRectangle(static_cast<int>(Wall.f_Position), 0, static_cast<int>(k_WallWidth), static_cast<int>(Wall.f_GapStart),
                GREEN);

  DrawRectangle(static_cast<int>(Wall.f_Position), static_cast<int>(Wall.f_GapStart + Wall.f_GapSize),
                static_cast<int>(k_WallWidth), g_ScreenHeight, GREEN);

}

} // namespace

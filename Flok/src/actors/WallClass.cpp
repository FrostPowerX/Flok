#include "WallClass.h"

#include "Constants.h"
#include "engine/SpriteManager.h"

namespace Actors {

constexpr float k_WallWidth = 50;
constexpr int k_MaxGapH = 300;

// TODO
//  Replace with player width
constexpr int k_MinGapH = 160;

int UniqueId = 0;

float GetRandomGapStart() {

  return static_cast<float>(GetRandomValue(0, g_ScreenHeight - k_MaxGapH));
}

float GetRandomGapHeight() {

  return static_cast<float>(GetRandomValue(k_MinGapH, k_MaxGapH));
}

WallType MakeWall(const float Speed) {

  return {.f_Sprite = Game::SpriteManager::GetSprite("Log")->f_Texture,
          .f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_WallWidth = k_WallWidth,
          .f_UniqueId = UniqueId++,
          .f_IsHidden = true,
          .f_checked = false};
}

void ResetWall(WallType& Wall, const float Speed) {

  Wall = {.f_Sprite = Game::SpriteManager::GetSprite("Log")->f_Texture,
          .f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_WallWidth = k_WallWidth,
          .f_UniqueId = Wall.f_UniqueId,
          .f_IsHidden = true,
          .f_checked = false};
}

void UpdateWalls(WallType& Wall) {

  Wall.f_Position -= Wall.f_Speed * GetFrameTime();
}

void DrawWalls(const WallType& Wall) {

  Rectangle source;
  source.x = 0;
  source.y = 0;
  source.width = static_cast<float>(Wall.f_Sprite.width);
  source.height = static_cast<float>(Wall.f_Sprite.height);

  Rectangle dest;
  dest.x = Wall.f_Position;
  dest.y = 0;
  dest.width = Wall.f_WallWidth;
  dest.height = Wall.f_GapStart;

  // Change to draw Texture
#ifndef _NDEBUG
  DrawRectangle(static_cast<int>(Wall.f_Position), 0, static_cast<int>(k_WallWidth), static_cast<int>(Wall.f_GapStart),
                GREEN);

  DrawRectangle(static_cast<int>(Wall.f_Position), static_cast<int>(Wall.f_GapStart + Wall.f_GapSize),
                static_cast<int>(k_WallWidth), g_ScreenHeight, GREEN);
#endif // !_DEBUG

  DrawTexturePro(Wall.f_Sprite, source, dest, Vector2{0, 0}, 0, WHITE);

  dest.y = Wall.f_GapStart + Wall.f_GapSize;
  dest.height = g_ScreenHeight;

  DrawTexturePro(Wall.f_Sprite, source, dest, Vector2{0, 0}, 0, WHITE);
}

} // namespace Actors

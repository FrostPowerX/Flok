#include "WallClass.h"

#include "Constants.h"

namespace {

constexpr float k_WallWidth = 100;
constexpr float k_MaxGapH = 300;
constexpr float k_MinGapH = 50;

int UniqueId = 0;



float GetRandomGapStart() {
  return static_cast<float>(GetRandomValue(0, g_ScreenHeight));
}



float GetRandomGapHeight() {
  return static_cast<float>(GetRandomValue(static_cast<int>(k_MinGapH),
                                           static_cast<int>(k_MaxGapH)));
}

};



Wall::WallType Wall::Make(float Speed) {

  return {.f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_IsHidden = true,
          .f_UniqueId = UniqueId++};
}



void Wall::Reset(WallType& Wall, const float Speed) {
  Wall = {.f_Position = g_ScreenWidth,
          .f_GapStart = GetRandomGapStart(),
          .f_GapSize = GetRandomGapHeight(),
          .f_Speed = Speed,
          .f_IsHidden = true,
          .f_UniqueId = Wall.f_UniqueId};
}



void Wall::Update(WallType& Wall) {
  Wall.f_Position -= Wall.f_Speed * GetFrameTime();
}



void Wall::Draw(const WallType& Wall) {
  //Change to draw Texture
  DrawRectangle(static_cast<int>(Wall.f_Position), 0,
                static_cast<int>(k_WallWidth),
                static_cast<int>(Wall.f_GapStart), GREEN);

  DrawRectangle(static_cast<int>(Wall.f_Position),
                static_cast<int>(Wall.f_GapStart + Wall.f_GapSize),
                static_cast<int>(k_WallWidth), g_ScreenHeight, GREEN);

}

#include "Parallax.h"

#include "Constants.h"

namespace Parallax {

Texture2D Background;
Texture2D Midground;
Texture2D Midground2;
Texture2D Frontground;

float f_Scrollingback = 0.0f;
float f_Scrollingmid = 0.0f;
float f_Scrollingmid2 = 0.0f;
float f_Scrollingfront = 0.0f;

void InitParallax() {

  Background = LoadTexture("res/JungleTileset/ParallaxBackground/Back.png");
  Midground = LoadTexture("res/JungleTileset/ParallaxBackground/Back2.png");
  Midground2 = LoadTexture("res/JungleTileset/ParallaxBackground/Back3.png");
  Frontground = LoadTexture("res/JungleTileset/ParallaxBackground/BushFront.png");

  Background.height = g_ScreenHeight;
  Background.width = g_ScreenWidth;

  Midground.height = g_ScreenHeight;
  Midground.width = g_ScreenWidth;

  Midground2.height = g_ScreenHeight;
  Midground2.width = g_ScreenWidth;

  Frontground.height = g_ScreenHeight;
  Frontground.width = g_ScreenWidth;

}

void UnloadParallax() {

  UnloadTexture(Background);
  UnloadTexture(Midground);
  UnloadTexture(Midground2);
  UnloadTexture(Frontground);

}

void UpdateParallax(const float Speed) {

  f_Scrollingmid -= Speed * 0.25f * GetFrameTime();
  f_Scrollingmid2 -= Speed * 0.5f * GetFrameTime();
  f_Scrollingfront -= Speed * GetFrameTime();

  if (f_Scrollingmid <= -Midground.width)
    f_Scrollingmid = 0;
  if (f_Scrollingmid2 <= -Midground2.width)
    f_Scrollingmid2 = 0;
  if (f_Scrollingfront <= -Frontground.width)
    f_Scrollingfront = 0;

}

void DrawBackground() {

  DrawTextureEx(Background, Vector2(f_Scrollingback, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(Background, Vector2(Background.width + f_Scrollingback, 0), 0.0f, 1.0f, WHITE);

}

void DrawMidground() {

  DrawTextureEx(Midground, Vector2(f_Scrollingmid, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(Midground, Vector2(Midground.width + f_Scrollingmid, 0), 0.0f, 1.0f, WHITE);

}

void DrawMidground2() {

  DrawTextureEx(Midground2, Vector2(f_Scrollingmid2, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(Midground2, Vector2{Midground2.width + f_Scrollingmid2, 0}, 0.0f, 1.0f, WHITE);

}

void DrawFrontground() {

  DrawTextureEx(Frontground, Vector2(f_Scrollingfront, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(Frontground, Vector2(Frontground.width + f_Scrollingfront, 0), 0.0f, 1.0f, WHITE);

}
} // namespace Parallax

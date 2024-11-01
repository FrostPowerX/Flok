#include "PlayerClass.h"

#include "Constants.h"
#include "engine/Math.h"

namespace {
PlayerClass::PlayerType Player;

}

void PlayerClass::Init() {
  Player.f_BoundingBox = {51, g_ScreenHeight - 101, 100, 100};
  Player.f_Direction = {1, 0};
}

void PlayerClass::Push(const Vector2& Direction, const float Force) {
  Vector2 Temp = Math::Multiply(Direction, Force * GetFrameTime());
  Temp = Math::Add(Player.f_Direction, Temp);
  Player.f_Direction = Math::Normalize(Temp, Math::GetMag(Temp));
  Player.f_Speed += Force * GetFrameTime();
}

void PlayerClass::Update() {
  //add gravity
  if (Player.f_BoundingBox.y > Player.f_BoundingBox.height / 2.0F && Player.
      f_BoundingBox.y < g_ScreenHeight - Player.f_BoundingBox.height / 2.0F) {
    Player.f_BoundingBox.y += Player.f_Direction.y * Player.f_Speed;
      } else if (Math::IsEqual(
          Player.f_BoundingBox.y + Player.f_BoundingBox.height / 2.0F,
          g_ScreenHeight)) {
        Player.f_Speed = 0;
        Player.f_Direction = {1, 0};
          }
}

void PlayerClass::Draw() {
  DrawRectanglePro(Player.f_BoundingBox,
                   {Player.f_BoundingBox.width / 2.0F,
                    Player.f_BoundingBox.height / 2.0F},
                   Math::GetRotation(Player.f_Direction), GREEN);
}

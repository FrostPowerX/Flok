#include "PlayerClass.h"

#include "Constants.h"
#include "engine/Collisions.h"
#include "engine/Math.h"

namespace {
PlayerClass::PlayerType Player;

}



void PlayerClass::Init() {
  Player.f_BoundingBox = {.x = 51,
                          .y = g_ScreenHeight - 101,
                          .width = 100,
                          .height = 100};
  Player.f_Direction = {.x = 1, .y = 0};
}



void PlayerClass::Push(const Vector2& Direction, const float Force) {
  Vector2 Temp = Math::Multiply(Direction, Force * GetFrameTime());
  Temp = Math::Add(Player.f_Direction, Temp);
  Player.f_Direction = Math::Normalize(Temp, Math::GetMag(Temp));
  Player.f_Speed += Force * GetFrameTime();
}



void PlayerClass::Update() {
  //add gravity
  if (!Collisions::IsRectBorder(Player.f_BoundingBox)) {
    Player.f_BoundingBox.y += Player.f_Direction.y * Player.f_Speed;
  }
}



void PlayerClass::Draw() {
  DrawRectanglePro(Player.f_BoundingBox,
                   {.x = Player.f_BoundingBox.width / 2.0F,
                    .y = Player.f_BoundingBox.height / 2.0F},
                   Math::GetRotation(Player.f_Direction), GREEN);
}



Rectangle PlayerClass::GetBoundingBox() {
  return Player.f_BoundingBox;
}

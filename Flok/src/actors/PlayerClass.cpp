#include "PlayerClass.h"

#include "Constants.h"
#include "engine/Collisions.h"
#include "engine/Math.h"

namespace {

constexpr float k_Gravity = 9.8F;
constexpr float k_SpeedLimit = 5.0F;

PlayerClass::PlayerType Player;
}



void PlayerClass::Init() {
  Player.f_BoundingBox = {.x = 51.0F,
                          .y = g_ScreenHeight / 2.0F,
                          .width = 32.0F,
                          .height = 32.0F};
  Player.f_Direction = {.x = 1, .y = 0};
}



void PlayerClass::Push(const Vector2& Direction, const float Force) {
  Vector2 Temp = Math::Multiply(Direction, Force * GetFrameTime());
  Temp = Math::Add(Player.f_Direction, Temp);
  Player.f_Direction = Math::Normalize(Temp, Math::GetMag(Temp));
  if (Player.f_Speed < k_SpeedLimit) {
    Player.f_Speed += Force * GetFrameTime();
  } else {
    Player.f_Speed = k_SpeedLimit;
  }
}



void PlayerClass::Update() {
  Push({.x = 0, .y = 1}, k_Gravity);
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



void PlayerClass::MovePlayer(const float Height) {
  Player.f_BoundingBox.y += Height;
}

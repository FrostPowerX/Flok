#include "PlayerClass.h"

#include "Constants.h"
#include "engine/Collisions.h"
#include "engine/Math.h"

namespace Actors {

constexpr float k_SpeedLimit = 50000.0F;
constexpr float k_FramesHop = 7.0F;
constexpr int k_Scale = 2;

void InitPlayer(PlayerType& Player, std::string TextPath) {
  Player.f_BoundingBox = {.x = 51.0F, .y = g_ScreenHeight / 2.0F, .width = 48.0F, .height = 48.0F};
  Player.f_Direction = {.x = 1, .y = 0};
  Player.f_Sprite = LoadTexture(TextPath.c_str());
  Player.f_FrameTimer = 0;
  Player.f_Speed = 0;
}

void UnloadPlayer(PlayerType& Player) {
  if (IsTextureReady(Player.f_Sprite)) {
    UnloadTexture(Player.f_Sprite);
  }
}

void PushPlayer(PlayerType& Player, const Vector2& Direction, float Force) {

  Vector2 Temp = Math::Multiply(Direction, Force * GetFrameTime());
  Temp = Math::Add(Player.f_Direction, Temp);

  // TODO
  //  Fix rotation so if it is aiming down, it remains looking forward
  //  Maybe use Player.f_Direction.x *= -1 if y is positive
  Player.f_Direction = Math::Normalize(Temp, Math::GetMag(Temp));

  if (Player.f_Speed < k_SpeedLimit && Direction.y > 0) {
    Player.f_Speed += Player.f_Direction.y + Force * GetFrameTime();
  } else if (Player.f_Speed < k_SpeedLimit) {
    Player.f_Speed += Player.f_Direction.y + (-Force);
  } else {
    Player.f_Speed = k_SpeedLimit;
  }
}

void UpdatePlayer(PlayerType& Player) {

  PushPlayer(Player, {.x = 0, .y = 1}, g_Gravity);

  if (!Collisions::IsRectBorder(Player.f_BoundingBox)) {
    Player.f_BoundingBox.y += Player.f_Direction.y * Player.f_Speed * GetFrameTime();
  }

  Player.f_FrameTimer += GetFrameTime();

  if (Player.f_FrameTimer >= g_Second / k_FramesHop) {

    Player.f_FrameTimer = 0;
    Player.f_Frame++;

    if (Player.f_Frame > k_FramesHop) {
      Player.f_Frame = 0;
    }
  }
}

void DrawPlayer(PlayerType& Player) {

#ifndef _DEBUG
  DrawRectangleLinesEx(Player.f_BoundingBox, 2, GREEN);
#endif // !_Debug

  Rectangle k_Source;
  k_Source.x = GetCenterPlayer(Player).x;
  k_Source.y = GetCenterPlayer(Player).y;
  k_Source.width = GetScaledSizePlayer(Player).x;
  k_Source.height = GetScaledSizePlayer(Player).y;

  Vector2 k_Origin;
  k_Origin.x = GetScaledSizePlayer(Player).x * 0.5f;
  k_Origin.y = GetScaledSizePlayer(Player).y * 0.5f;

  DrawTexturePro(Player.f_Sprite, {.x = 48 * (Player.f_Frame * 2 + 1), .y = 8, .width = 48, .height = 32}, k_Source,
                 k_Origin, 0.0F, WHITE);
}

Rectangle GetBoundingBoxPlayer(PlayerType& Player) {

  return Player.f_BoundingBox;
}

Vector2 GetCenterPlayer(PlayerType Player) {

  Vector2 center;

  center.x = Player.f_BoundingBox.x + Player.f_BoundingBox.width * 0.5f;
  center.y = Player.f_BoundingBox.y + Player.f_BoundingBox.height * 0.5f;

  return center;
}

Vector2 GetScaledSizePlayer(PlayerType Player) {

  Vector2 scaledSize;

  scaledSize.x = Player.f_BoundingBox.width * k_Scale;
  scaledSize.y = Player.f_BoundingBox.height * k_Scale;

  return scaledSize;
}

void SetPositionPlayer(PlayerType& Player, float X, float Y) {

  Player.f_BoundingBox.x = X;
  Player.f_BoundingBox.y = Y;
}

void MovePlayer(PlayerType& Player, float Height) {

  Player.f_BoundingBox.y += Height;
}

float GetSpeedPlayer(PlayerType& Player) {

  return Player.f_Speed;
}

} // namespace Actors

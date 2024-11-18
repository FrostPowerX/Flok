#pragma once

#include <iostream>

#include "raylib.h"

namespace Actors {

struct PlayerType {
  Rectangle f_BoundingBox;
  Vector2 f_Direction;
  float f_Speed;
  float f_FrameTimer;
  float f_Frame;
  Texture2D f_Sprite;
};

void InitPlayer(PlayerType& Player, std::string TextPath);

void PushPlayer(PlayerType& Player, const Vector2& Direction, float Force);

void UpdatePlayer(PlayerType& Player);

void DrawPlayer(PlayerType& Player);

Rectangle GetBoundingBoxPlayer(PlayerType& Player);

void SetPositionPlayer(PlayerType& Player, float x, float y);

void MovePlayer(PlayerType& Player, float Height);

float GetSpeedPlayer(PlayerType& Player);

Vector2 GetCenterPlayer(PlayerType Player);

Vector2 GetScaledSizePlayer(PlayerType Player);

} // namespace Actors

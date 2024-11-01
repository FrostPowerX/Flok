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


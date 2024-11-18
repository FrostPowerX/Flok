#pragma once

#include <string>
#include <vector>

#include "raylib.h"

namespace Game {
namespace SpriteManager {
const int textureWidth = 32;
const int textureHeight = 32;

struct Sprite {
  Texture2D texture;
  std::string name;
};

struct Graphic {
  Texture2D sprite;

  Rectangle source;
  Rectangle dest;
  Vector2 origin;
};

Sprite* GetSprite(std::string name);

void LoadSprites();
void UnloadSprites();
} // namespace SpriteManager
} // namespace Game

#pragma once

#include <string>
#include <vector>

#include "raylib.h"

namespace Game {
namespace SpriteManager {
const int k_TextureWidth = 32;
const int k_TextureHeight = 32;

struct Sprite {
  Texture2D f_Texture;
  std::string f_Name;
};

Sprite* GetSprite(std::string Name);

void LoadSprites();
void UnloadSprites();
} // namespace SpriteManager
} // namespace Game

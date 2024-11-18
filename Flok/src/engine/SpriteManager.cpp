#include "SpriteManager.h"

namespace Game {
namespace SpriteManager {
std::vector<Sprite*> sprites;

void AddSprite(std::string name, std::string path, bool reescale = false);

void AddSprite(std::string name, std::string path, bool reescale) {
  Sprite* newSp = new Sprite();
  newSp->name = name;
  newSp->texture = LoadTexture(path.c_str());

  if (reescale) {
    newSp->texture.width = 32;
    newSp->texture.height = 32;
  }

  sprites.push_back(newSp);
}

Sprite* GetSprite(std::string name) {
  if (sprites.size() <= 0)
    return nullptr;

  for (int i = 0; i < static_cast<int>(sprites.size()); i++) {
    if (name == sprites[i]->name)
      return sprites[i];
  }

  return nullptr;
}

void LoadSprites() {
  AddSprite("BackGround", "res/JungleTileset/ParallaxBackground/Back.png");
  AddSprite("MidGround", "res/JungleTileset/ParallaxBackground/Back2.png");
  AddSprite("MidGround2", "res/JungleTileset/ParallaxBackground/Back3.png");
  AddSprite("FrontGround", "res/JungleTileset/ParallaxBackground/BushFront.png");

  AddSprite("Player1", "res/ToxicFrog/BlueBlue/ToxicFrogBlueBlue_Hop.png");
  AddSprite("Player2", "res/ToxicFrog/GreenBlue/ToxicFrogGreenBlue_Hop.png");
  //AddSprite("Tube", "");
}

void UnloadSprites() {
  int size = sprites.size();

  for (int i = 0; i < size; i++) {
    UnloadTexture(sprites[i]->texture);
  }

  for (int i = 0; i < size; i++) {
    delete sprites[i];
  }
}

} // namespace SpriteManager
} // namespace Game

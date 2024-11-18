#include "SpriteManager.h"

namespace Game {
namespace SpriteManager {
std::vector<Sprite*> f_Sprites;

void AddSprite(std::string Name, std::string Path, bool Reescale = false);

void AddSprite(std::string Name, std::string Path, bool Reescale) {
  Sprite* NewSp = new Sprite();
  NewSp->f_Name = Name;
  NewSp->f_Texture = LoadTexture(Path.c_str());

  if (Reescale) {
    NewSp->f_Texture.width = 32;
    NewSp->f_Texture.height = 32;
  }

  f_Sprites.push_back(NewSp);
}

Sprite* GetSprite(std::string Name) {
  if (f_Sprites.size() <= 0)
    return nullptr;

  for (int i = 0; i < static_cast<int>(f_Sprites.size()); i++) {
    if (Name == f_Sprites[i]->f_Name)
      return f_Sprites[i];
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
  int Size = f_Sprites.size();

  if (Size <= 0)
      return;

  for (int i = 0; i < Size; i++) {
    UnloadTexture(f_Sprites[i]->f_Texture);
  }

  for (int i = 0; i < Size; i++) {
    delete f_Sprites[i];
  }
}

} // namespace SpriteManager
} // namespace Game

#include "CloseUp.h"

#include "raylib.h"

#include "engine/SoundManager.h"
#include "engine/SpriteManager.h"
#include "engine/GameManager.h"

namespace Game {

void Close() {

  SpriteManager::UnloadSprites();
  SoundManager::UnloadSounds();

  UnloadGManager();

  CloseAudioDevice();
  CloseWindow();
}

} // namespace Game

#include "CloseUp.h"

#include "raylib.h"

#include "engine/SoundManager.h"
#include "engine/SpriteManager.h"

namespace Game {

void Close() {

  SpriteManager::UnloadSprites();
  SoundManager::UnloadSounds();

  CloseAudioDevice();
  CloseWindow();
}

} // namespace Game

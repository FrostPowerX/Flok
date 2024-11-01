#include "CloseUp.h"

#include "raylib.h"

#include "ResManager.h"



void CloseUp::Close() {
  for (int Resource = 0; Resource < static_cast<int>(
                           ResManager::Resources::Last); Resource++) {

    switch (static_cast<ResManager::Resources>(Resource)) {
      case ResManager::Resources::AlmendraDisplay:
        UnloadFont(GetFont(ResManager::Resources::AlmendraDisplay));
        break;

      case ResManager::Resources::Background:
        __fallthrough case ResManager::Resources::PlayerSprite:
        __fallthrough case ResManager::Resources::DemonSpriteMove:
        __fallthrough case ResManager::Resources::BulletSprite:
        __fallthrough case ResManager::Resources::HeartSprite:
        __fallthrough case ResManager::Resources::HeartBackground:
        __fallthrough case ResManager::Resources::Buttons:
        __fallthrough case ResManager::Resources::PauseBG:
        UnloadTexture(GetTexture(static_cast<ResManager::Resources>(Resource)));
        break;

      case ResManager::Resources::MainMenuMusic:
        __fallthrough case ResManager::Resources::GameMusic:
        UnloadMusicStream(
            GetMusic(static_cast<ResManager::Resources>(Resource)));
        break;

      case ResManager::Resources::Shoot:
        __fallthrough case ResManager::Resources::Hit:
        __fallthrough case ResManager::Resources::Dropship:
        __fallthrough case ResManager::Resources::MenuOpen:
        __fallthrough case ResManager::Resources::MenuHover:
        UnloadSound(GetSound(static_cast<ResManager::Resources>(Resource)));
        break;
      case ResManager::Resources::Last:
        //pass
        break;

    }
  }
  CloseAudioDevice();
  CloseWindow();
}

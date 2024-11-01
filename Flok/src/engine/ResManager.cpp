#include "ResManager.h"

#include <string>

#include "raylib.h"

#include "Error.h"

namespace {

#pragma region Fonts

Font MissingFont;

#pragma endregion

#pragma region Textures

Texture2D MissingTexture;

#pragma endregion

#pragma region SFX

Music MissingMusic;
Sound MissingSound;

#pragma endregion

}



std::string ResManager::ResourceToString(const Resources Resource) {
  switch (Resource) {
    default:
      return "unknown";
  }
}



Texture2D& ResManager::GetTexture(const Resources Resource) {

  switch (Resource) {
    
    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingTexture;
}



Music& ResManager::GetMusic(const Resources Resource) {

  switch (Resource) {
    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingMusic;
}



Sound& ResManager::GetSound(const Resources Resource) {

  switch (Resource) {
    
    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingSound;
}



Font& ResManager::GetFont(const Resources Resource) {

  switch (Resource) {
    case Resources::AlmendraDisplay:
    
    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingFont;
}



void ResManager::MakeFonts() {
}



void ResManager::MakeTextures() {
}



void ResManager::MakeSounds() {

}



void ResManager::MakeMusic() {

}

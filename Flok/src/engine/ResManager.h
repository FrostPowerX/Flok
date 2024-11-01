#pragma once
#include <string>

#include "raylib.h"

namespace ResManager {

enum class Resources {

};



Texture2D& GetTexture(Resources Resource);

Music& GetMusic(Resources Resource);

Sound& GetSound(Resources Resource);

Font& GetFont(Resources Resource);

void MakeFonts();

void MakeTextures();

void MakeSounds();

void MakeMusic();

std::string ResourceToString(Resources Resource);
};

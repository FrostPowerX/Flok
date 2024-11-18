#pragma once

#include <string>

#include "raylib.h"

namespace Game {
namespace SoundManager {
struct SoundBox {
  Sound f_Music;
  std::string f_Name;

  bool f_Loop;
};

struct MusicBox {
  Music f_Music;
  std::string f_Name;

  bool f_Loop;
};

extern float f_Volume;

void Update();

void PlayS(std::string Name);
void StopS(std::string Name);

void PlayM(std::string Name);
void StopM(std::string Name);

void LoadSounds();
void UnloadSounds();

} // namespace SoundManager
} // namespace Game

#pragma once

#include <string>

#include "raylib.h"

namespace Game {
namespace SoundManager {
struct SoundBox {
  Sound music;
  std::string name;

  bool loop;
};

struct MusicBox {
  Music music;
  std::string name;

  bool loop;
};

extern float volume;

void Update();

void PlayS(std::string name);
void StopS(std::string name);

void PlayM(std::string name);
void StopM(std::string name);

void LoadSounds();
void UnloadSounds();
} // namespace SoundManager
} // namespace Game

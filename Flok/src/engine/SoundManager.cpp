#include "SoundManager.h"

#include <vector>

namespace Game {
namespace SoundManager {
float volume = 1;

std::vector<SoundBox*> sounds;
std::vector<MusicBox*> musics;

Music currentMusic;

void AddSound(std::string name, std::string path, bool loop = false);
void AddMusic(std::string name, std::string path, bool loop = false);

void AddSound(std::string name, std::string path, bool loop) {
  SoundBox* newS = new SoundBox();
  newS->name = name;
  newS->music = LoadSound(path.c_str());
  newS->loop = loop;

  sounds.push_back(newS);
}

void AddMusic(std::string name, std::string path, bool loop) {
  MusicBox* newM = new MusicBox();
  newM->name = name;
  newM->music = LoadMusicStream(path.c_str());
  newM->loop = loop;

  musics.push_back(newM);
}

void Update() {
  UpdateMusicStream(currentMusic);
}

void PlayS(std::string name) {
  if (sounds.size() <= 0)
    return;

  Sound music{};

  for (int i = 0; i < static_cast<int>(sounds.size()); i++) {
    if (sounds[i] != nullptr)
      if (name == sounds[i]->name)
        music = sounds[i]->music;
  }

  if (!IsSoundPlaying(music))
    PlaySound(music);

  SetSoundVolume(music, volume);
}

void StopS(std::string name) {
  if (sounds.size() <= 0)
    return;

  Sound music{};

  for (int i = 0; i < static_cast<int>(sounds.size()); i++) {
    if (sounds[i] != nullptr)
      if (name == sounds[i]->name)
        music = sounds[i]->music;
  }

  if (IsSoundPlaying(music))
    StopSound(music);
}

void PlayM(std::string name) {
  if (sounds.size() <= 0)
    return;

  Music music{};

  for (int i = 0; i < static_cast<int>(musics.size()); i++) {
    if (musics[i] != nullptr)
      if (name == musics[i]->name)
        music = musics[i]->music;
  }

  PlayMusicStream(music);

  currentMusic = music;

  SetMusicVolume(music, volume);
}

void StopM(std::string name) {
  if (sounds.size() <= 0)
    return;

  Music music{};

  for (int i = 0; i < static_cast<int>(musics.size()); i++) {
    if (musics[i] != nullptr)
      if (name == musics[i]->name)
        music = musics[i]->music;
  }

  StopMusicStream(music);

  currentMusic = Music();
}

void LoadSounds() {

}

void UnloadSounds() {
  int size = sounds.size();

  for (int i = 0; i < size; i++) {
    UnloadSound(sounds[i]->music);
  }

  for (int i = 0; i < size; i++) {
    delete sounds[i];
  }

  int sizeM = musics.size();

  for (int i = 0; i < sizeM; i++) {
    UnloadMusicStream(musics[i]->music);
  }

  for (int i = 0; i < sizeM; i++) {
    delete musics[i];
  }
}
} // namespace SoundManager
} // namespace Game

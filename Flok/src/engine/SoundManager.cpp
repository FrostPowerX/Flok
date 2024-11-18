#include "SoundManager.h"

#include <vector>

namespace Game {
namespace SoundManager {
float f_Volume = 1;

std::vector<SoundBox*> f_Sounds;
std::vector<MusicBox*> f_Musics;

Music f_CurrentMusic;

void AddSound(std::string f_Name, std::string path, bool f_Loop = false);
void AddMusic(std::string f_Name, std::string path, bool f_Loop = false);

void AddSound(std::string Name, std::string Path, bool Loop) {
  SoundBox* NewS = new SoundBox();
  NewS->f_Name = Name;
  NewS->f_Music = LoadSound(Path.c_str());
  NewS->f_Loop = Loop;

  f_Sounds.push_back(NewS);
}

void AddMusic(std::string Name, std::string Path, bool Loop) {
  MusicBox* NewM = new MusicBox();
  NewM->f_Name = Name;
  NewM->f_Music = LoadMusicStream(Path.c_str());
  NewM->f_Loop = Loop;

  f_Musics.push_back(NewM);
}

void Update() {
  UpdateMusicStream(f_CurrentMusic);
}

void PlayS(std::string Name) {
  if (f_Sounds.size() <= 0)
    return;

  Sound Sound{};

  for (int i = 0; i < static_cast<int>(f_Sounds.size()); i++) {
    if (f_Sounds[i] != nullptr)
      if (Name == f_Sounds[i]->f_Name)
        Sound = f_Sounds[i]->f_Music;
  }

  // if (!IsSoundPlaying(Sound))
  PlaySound(Sound);

  SetSoundVolume(Sound, f_Volume);
}

void StopS(std::string Name) {
  if (f_Sounds.size() <= 0)
    return;

  Sound Music{};

  for (int i = 0; i < static_cast<int>(f_Sounds.size()); i++) {
    if (f_Sounds[i] != nullptr)
      if (Name == f_Sounds[i]->f_Name)
        Music = f_Sounds[i]->f_Music;
  }

  if (IsSoundPlaying(Music))
    StopSound(Music);
}

void PlayM(std::string Name) {
  if (f_Sounds.size() <= 0)
    return;

  Music f_Music{};

  for (int i = 0; i < static_cast<int>(f_Musics.size()); i++) {
    if (f_Musics[i] != nullptr)
      if (Name == f_Musics[i]->f_Name)
        f_Music = f_Musics[i]->f_Music;
  }

  PlayMusicStream(f_Music);

  f_CurrentMusic = f_Music;

  SetMusicVolume(f_Music, f_Volume);
}

void StopM(std::string Name) {
  if (f_Sounds.size() <= 0)
    return;

  Music f_Music{};

  for (int i = 0; i < static_cast<int>(f_Musics.size()); i++) {
    if (f_Musics[i] != nullptr)
      if (Name == f_Musics[i]->f_Name)
        f_Music = f_Musics[i]->f_Music;
  }

  StopMusicStream(f_Music);

  f_CurrentMusic = Music();
}

void LoadSounds() {

  AddSound("Crash", "res/Sounds/Crash.wav");
  AddSound("Enter", "res/Sounds/Enter.wav");
  AddSound("Fall", "res/Sounds/Fall.wav");

  AddSound("Jump1", "res/Sounds/Jump1.wav");
  AddSound("Jump2", "res/Sounds/Jump2.wav");
  AddSound("Jump3", "res/Sounds/Jump3.wav");
  AddSound("Jump4", "res/Sounds/Jump4.wav");

  AddSound("Point1", "res/Sounds/Point1.wav");
  AddSound("Point2", "res/Sounds/Point2.wav");
  AddSound("Point3", "res/Sounds/Point3.wav");

  AddSound("Pause", "res/Sounds/Pause.wav");
  AddSound("UnPause", "res/Sounds/UnPause.wav");

  AddSound("Select", "res/Sounds/Select.wav");
  AddSound("Back", "res/Sounds/Back.wav");

  AddMusic("Menu", "res/Music/Menu.wav", true);
  AddMusic("GamePlay", "res/Music/GamePlay.wav", true);
}

void UnloadSounds() {
  int Size = f_Sounds.size();

  if (Size > 0) {
    for (int i = 0; i < Size; i++) {
      UnloadSound(f_Sounds[i]->f_Music);
    }

    for (int i = 0; i < Size; i++) {
      delete f_Sounds[i];
    }
  }

  int SizeM = f_Musics.size();

  if (SizeM > 0) {
    for (int i = 0; i < SizeM; i++) {
      UnloadMusicStream(f_Musics[i]->f_Music);
    }

    for (int i = 0; i < SizeM; i++) {
      delete f_Musics[i];
    }
  }
}
} // namespace SoundManager
} // namespace Game

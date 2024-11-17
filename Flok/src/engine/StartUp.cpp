﻿#include "StartUp.h"

#include <iostream>

#include "raylib.h"

#include "Constants.h"
#include "SceneManager.h"

#include "engine/GameManager.h"

namespace Game {

void Load() {

  InitWindow(g_ScreenWidth, g_ScreenHeight, "Flok");

  SetWindowState(FLAG_VSYNC_HINT);

  InitAudioDevice();

  HideCursor();

  InitGManager();

  if (!IsAudioDeviceReady()) {
    std::cerr << "Error setting up Audio device" << '\n';
  }

  SetExitKey(KEY_NULL);

  SceneManager::ChangeScene();
}

} // namespace Game

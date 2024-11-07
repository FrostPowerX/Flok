#include "StartUp.h"

#include <iostream>

#include "raylib.h"

#include "Constants.h"
/*
#include "ResManager.h"
*/
#include "SceneManager.h"

namespace {

}



void StartUp::Load() {

  InitWindow(g_ScreenWidth, g_ScreenHeight, "Flok");

  SetWindowState(FLAG_VSYNC_HINT);

  InitAudioDevice();

  if (!IsAudioDeviceReady()) {
    std::cerr << "Error setting up Audio device" << '\n';
  }

  SetExitKey(KEY_NULL);

  SceneManager::ChangeScene();
}

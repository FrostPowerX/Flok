#include "CloseUp.h"

#include "raylib.h"



void CloseUp::Close() {

  CloseAudioDevice();
  CloseWindow();
}

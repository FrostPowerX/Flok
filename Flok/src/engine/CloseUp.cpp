#include "CloseUp.h"

#include "raylib.h"

/*
#include "ResManager.h"
*/



void CloseUp::Close() {
  
  CloseAudioDevice();
  CloseWindow();
}

#include "CloseUp.h"

#include "raylib.h"

namespace Game {

void Close() {

  CloseAudioDevice();
  CloseWindow();
}

} // namespace Game

#include "Credits.h"

#include "actors/PlayerClass.h"
#include "engine/SceneManager.h"

namespace  {

bool Exit = false;


void Input() {
  if (IsKeyReleased(KEY_ENTER)) {
    Exit = true;
  }
}

void Draw() {
// TODO
  // improve this
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    DrawText("Made by Nicolas Gallardo", 100, 100, 20, LIGHTGRAY);
    DrawText("Art by Eduardo Scarpato (https://im-dagon.itch.io/)", 140, 200, 20, LIGHTGRAY);
    DrawText("\t Toxic Frog https://tinyurl.com/toxic-frog", 180, 200, 20, LIGHTGRAY);
    DrawText("\t Forest Tileset https://tinyurl.com/ForestTitleSet", 180, 200, 20, LIGHTGRAY);
  }
  EndDrawing();
}

}

void Credits::Credits() {

  while (!Exit && !WindowShouldClose()) {
    Input();
    Draw();
  }
  ChangeScene(SceneManager::Scenes::MainMenu);
}

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

    DrawText("Made by Nicolas Gallardo", 100, 140, 20, LIGHTGRAY);
    DrawText("Art by Eduardo Scarpato (https://im-dagon.itch.io/)", 100, 200, 20, LIGHTGRAY);
    DrawText("\t Toxic Frog https://tinyurl.com/toxic-frog", 100, 260, 20, LIGHTGRAY);
    DrawText("\t Forest Tileset https://tinyurl.com/ForestTitleSet", 100, 320, 20, LIGHTGRAY);
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

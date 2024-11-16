#include "Credits.h"

#include "actors/PlayerClass.h"
#include "engine/SceneManager.h"

namespace Game {

namespace Scene {

static bool Exit = false;

static void InputButton() {
  if (IsKeyReleased(KEY_ENTER)) {
    Exit = true;
  }
}

static void Draw() {
  // TODO
  // improve this
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    DrawText("Made by Nicolas Gallardo", 100, 140, 20, BLACK);
    DrawText("\t Collaborate Emanuel Parajon", 100, 160, 20, BLACK);
    DrawText("Art by Eduardo Scarpato (https://im-dagon.itch.io/)", 100, 200, 20, BLACK);
    DrawText("\t Toxic Frog https://tinyurl.com/toxic-frog", 100, 260, 20, BLACK);
    DrawText("\t Forest Tileset https://tinyurl.com/ForestTitleSet", 100, 320, 20, BLACK);
  }
  EndDrawing();
}

void Credits() {

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Draw();
  }
  Exit = false;
  ChangeScene(SceneManager::Scenes::MainMenu);
}

} // namespace Scene

} // namespace Game

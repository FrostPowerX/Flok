#include "Credits.h"
#include "actors/PlayerClass.h"
#include "engine/SceneManager.h"

namespace Game {

namespace Scene {

static bool Exit = false;

static void InputButton() {

  if (IsKeyReleased(KEY_ESCAPE)) {
    Exit = true;
  }
}

static void Draw() {

  // TODO
  // improve this
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    DrawText("Controls: ", 100, 140, 20, BLACK);
    DrawText("\t Player 1: Jump = Space", 100, 160, 20, BLACK);
    DrawText("\t\t Player 1 frog: Blue", 100, 180, 20, BLACK);

    DrawText("\t Player 2: Jump = Arrow Up", 100, 220, 20, BLACK);
    DrawText("\t\t Player 2 frog: Green", 100, 240, 20, BLACK);

    DrawText("Pause/Back = Escape", 100, 300, 20, BLACK);
  }
  EndDrawing();
}

static void Unload() {

  Exit = false;

  ChangeScene(SceneManager::Scenes::MainMenu);
}

void Controls() {

  while (!Exit && !WindowShouldClose()) {

    InputButton();

    Draw();
  }

  Unload();
}

} // namespace Scene

} // namespace Game

#include "Credits.h"
#include "actors/PlayerClass.h"
#include "engine/Parallax.h"
#include "engine/SceneManager.h"
#include "engine/SoundManager.h"

namespace Game {

namespace Scene {

static bool Exit = false;

static void Init() {

  Parallax::RestartParallax();
}

static void InputButton() {

  if (IsKeyReleased(KEY_ESCAPE)) {
    Game::SoundManager::PlayS("Back");
    Exit = true;
  }
}

static void Draw() {

  // TODO
  // improve this
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    Parallax::DrawBackground();

    DrawText("Controls: ", 100, 140, 20, BLACK);
    DrawText("\t Player 1: Jump = Space", 100, 160, 20, BLACK);
    DrawText("\t\t Player 1 frog: Blue", 100, 180, 20, BLACK);

    DrawText("\t Player 2: Jump = ArrowUp", 100, 220, 20, BLACK);
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

  Init();

  while (!Exit && !WindowShouldClose()) {

    InputButton();
    Game::SoundManager::Update();
    Draw();
  }

  Unload();
}

} // namespace Scene

} // namespace Game

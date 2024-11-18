#include "Statistics.h"

#include <iostream>
#include <string>

#include "raylib.h"

#include "Constants.h"
#include "engine/Parallax.h"
#include "engine/GameManager.h"
#include "engine/SceneManager.h"
#include "engine/SoundManager.h"

namespace Game {
namespace Scene {

static bool f_IsMP = false;

static bool Exit = false;

static void Init() {

  f_IsMP = false;

  Parallax::RestartParallax();
}

static void InputButton() {

  if (IsKeyReleased(KEY_ESCAPE)) {

    Game::SoundManager::PlayS("Back");
    Exit = true;
  }

  if (IsKeyReleased(KEY_R)) {

    Game::SoundManager::PlayS("Enter");
    f_IsMP = !f_IsMP;
  }
}

static void Draw() {

  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    Parallax::DrawBackground();

    std::string Title = (f_IsMP) ? "Multi Player" : "Single Player";
    std::string TotalScore = "Total Score: " + std::to_string(GetTotalScore(f_IsMP));
    std::string TotalJumps = "Total Jumps: " + std::to_string(GetTotalJumps(f_IsMP));
    std::string TotalLose = "Total Lose: " + std::to_string(GetTotalLose(f_IsMP));
    std::string MaxScore = "Max Score: " + std::to_string(GetMaxScore(f_IsMP));

    DrawText(Title.c_str(), (g_ScreenWidth - MeasureText(Title.c_str(), 50)) / 2, 64, 50, BLACK);
    DrawText(MaxScore.c_str(), (g_ScreenWidth - MeasureText(MaxScore.c_str(), 30)) / 2, 124, 30, BLACK);

    DrawText(TotalScore.c_str(), g_ScreenWidth / 4, 200, 20, BLACK);
    DrawText(TotalJumps.c_str(), g_ScreenWidth / 4, 220, 20, BLACK);
    DrawText(TotalLose.c_str(), g_ScreenWidth / 4, 240, 20, BLACK);

    DrawText("Alternate Single/Multi = R", 10, g_ScreenHeight - 30, 10, BLACK);
    DrawText("Back = Escape", 10, g_ScreenHeight - 20, 10, BLACK);
  }
  EndDrawing();
}

static void Unload() {

  Exit = false;
  ChangeScene(SceneManager::Scenes::MainMenu);
}

void Statistics() {

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

#include "Lose.h"

#include <iostream>

#include "raylib.h"

#include "Constants.h"
#include "engine/Buttons.h"
#include "engine/GameManager.h"
#include "engine/Layout.h"
#include "engine/Parallax.h"
#include "engine/SceneManager.h"
#include "engine/SoundManager.h"

namespace Game {

namespace Scene {

static constexpr int k_MaxButtons = 2;
static constexpr int k_Fontsize = 32;

static UI::Button f_Buttons[k_MaxButtons];
static SceneManager::Scenes f_SelectedScene;

static int Hovering = 1;

static bool f_IsMP;

static bool Exit = false;

static void Init() {
  Hovering = 1;

  Parallax::RestartParallax();

  f_SelectedScene = SceneManager::Scenes::MainMenu;

  constexpr Layout::Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Layout::Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < k_MaxButtons; I++) {

    switch (I) {
      case 0:
        Text = "Restart";
        break;
      case 1:
        Text = "Menu";
        break;
    }

    UI::CreateButton(f_Buttons[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

static void InputButton() {

  UI::InputButton(f_Buttons, Hovering, k_MaxButtons);

  if (IsKeyReleased(KEY_ENTER)) {

    Game::SoundManager::PlayS("Enter");

    switch (Hovering) {

      case 1:

        if (f_IsMP) {
          f_SelectedScene = SceneManager::Scenes::Multiplayer;
        } else {

          f_SelectedScene = SceneManager::Scenes::Play;
        }
        break;
    }

    Exit = true;
  }
}

static void Draw() {
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    Parallax::DrawBackground();
    Parallax::DrawMidground();
    Parallax::DrawMidground2();

    UI::RenderButtons(f_Buttons, k_MaxButtons);

    const std::string k_MaxScoreShow = "Score: " + std::to_string(GetScore(f_IsMP));

    DrawText("Game Over", (g_ScreenWidth - MeasureText("Game Over", 50)) / 2, 64, 50, BLACK);
    DrawText(k_MaxScoreShow.c_str(), (g_ScreenWidth - MeasureText(k_MaxScoreShow.c_str(), 20)) / 2, 124, 20, BLACK);

    DrawText("Select = ArrowUp / ArrowDown", 10, g_ScreenHeight - 30, 10, BLACK);
    DrawText("Enter = Enter", 10, g_ScreenHeight - 20, 10, BLACK);
  }
  EndDrawing();
}

static void Unload() {

  HideCursor();

  ResetScore(f_IsMP);

  Exit = false;
  ChangeScene(f_SelectedScene);
}

void Lose(bool IsMP) {

  Init();

  f_IsMP = IsMP;

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Game::SoundManager::Update();
    Draw();
  }

  Unload();
}

} // namespace Scene
} // namespace Game

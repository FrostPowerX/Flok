#include "MainMenu.h"

#include <array>
#include <string>

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

using namespace UI;

static constexpr int k_Amount = 6;
static constexpr int k_Fontsize = 32;

static Button MainMenuButtons[k_Amount];
static const std::string k_GameVer = "v0.4";

static int Hovering = 1;

static auto SelectedScene = SceneManager::Scenes::Exit;

static bool Exit;

static void Init() {

  SelectedScene = SceneManager::Scenes::Exit;
  Exit = false;
  Hovering = 1;

  //SoundManager::StopM("GamePlay");
  SoundManager::PlayM("Menu");

  Parallax::RestartParallax();

  constexpr Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < k_Amount; I++) {

    switch (I) {

      case 0:
        Text = "Singleplayer";
        break;

      case 1:
        Text = "Multiplayer";
        break;

      case 2:
        Text = "Statistics";
        break;

      case 3:
        Text = "Controls";
        break;

      case 4:
        Text = "Credits";
        break;

      case 5:
        Text = "Exit";
        break;

      default:
        Text = "NULL";
    }

    UI::CreateButton(MainMenuButtons[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

static void InputButton() {

  if (IsKeyReleased(KEY_ESCAPE)) {
    Exit = true;
  }

  UI::InputButton(MainMenuButtons, Hovering, k_Amount);

  if (IsKeyReleased(KEY_ENTER)) {

    Game::SoundManager::PlayS("Enter");

    SelectedScene = static_cast<SceneManager::Scenes>(Hovering);
    Exit = true;
  }
}

static void Draw() {

  constexpr int k_FontSizeTitle = 32;

  const std::string k_MaxScoreShow = "Max Socre: " + std::to_string(GetMaxScore());
  const std::string k_MaxScoreShowMP = "Max SocreMP: " + std::to_string(GetMaxScore(true));

  BeginDrawing();

  ClearBackground(RAYWHITE);

  Parallax::DrawBackground();

  DrawText("Flok", (g_ScreenWidth - MeasureText("Flok", k_FontSizeTitle)) / 2, 64, k_FontSizeTitle, BLACK);

  if (GetMaxScore() > 0) {

    DrawText(k_MaxScoreShow.c_str(), (g_ScreenWidth - MeasureText(k_MaxScoreShow.c_str(), k_FontSizeTitle / 2)) / 2,
             104, k_FontSizeTitle / 2, BLACK);
  }

  if (GetMaxScore(true) > 0) {

    DrawText(k_MaxScoreShowMP.c_str(), (g_ScreenWidth - MeasureText(k_MaxScoreShowMP.c_str(), k_FontSizeTitle / 2)) / 2,
             144, k_FontSizeTitle / 2, BLACK);
  }

  RenderButtons(MainMenuButtons, k_Amount);

  DrawText(k_GameVer.c_str(), 10, 10, 10, BLACK);

  DrawText("Select = ArrowUp / ArrowDown", 10, g_ScreenHeight - 40, 10, BLACK);
  DrawText("Enter = Enter", 10, g_ScreenHeight - 30, 10, BLACK);
  DrawText("Exit = Escape", 10, g_ScreenHeight - 20, 10, BLACK);

  EndDrawing();
}

static void Unload() {
  // TODO

  ChangeScene(SelectedScene);
}

void Menu() {
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

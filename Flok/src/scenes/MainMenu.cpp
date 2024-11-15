#include "MainMenu.h"

#include <array>
#include <string>

#include "raylib.h"

#include "Constants.h"
#include "engine/Buttons.h"
#include "engine/Layout.h"
#include "engine/SceneManager.h"

namespace game {

namespace scenes {

using namespace Buttons;

const std::string k_GameVer = "v0.4";
constexpr int k_Amount = 4;
constexpr int k_Fontsize = 32;

Button MainMenuButtons[k_Amount];
bool Exit;
auto SelectedScene = SceneManager::Scenes::Exit;
int Hovering = 1;

void Init() {
  SelectedScene = SceneManager::Scenes::Exit;
  Exit = false;
  Hovering = 1;

  constexpr Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < k_Amount; I++) {

    switch (I) {
      case 0:
        Text = "Play";
        break;
      case 1:
        Text = "Multiplayer";
        break;
      case 2:
        Text = "Credits";
        break;
      case 3:
        Text = "Exit";
        break;
      default:
        Text = "NULL";
    }

    Buttons::Create(MainMenuButtons[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

void Unload() {
  // TODO
}

void Input() {
  Buttons::Input(MainMenuButtons, Hovering, k_Amount);

  if (IsKeyReleased(KEY_ENTER)) {
    SelectedScene = static_cast<SceneManager::Scenes>(Hovering);
    Exit = true;
  }
}

void Draw() {

  constexpr int k_FontSizeTitle = 32;

  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Flok", (g_ScreenWidth - MeasureText("Flok", k_FontSizeTitle)) / 2, 64, k_FontSizeTitle, BLACK);

  RenderButtons(MainMenuButtons, k_Amount);

  DrawText(k_GameVer.c_str(), 10, 10, 10, BLACK);

  EndDrawing();
}

void Menu() {
  Init();

  while (!Exit && !WindowShouldClose()) {
    Input();
    Draw();
  }

  Unload();
  ChangeScene(SelectedScene);
}

} // namespace scenes
} // namespace game

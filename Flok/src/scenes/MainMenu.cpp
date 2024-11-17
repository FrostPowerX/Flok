#include "MainMenu.h"

#include <array>
#include <string>

#include "raylib.h"

#include "Constants.h"
#include "engine/Buttons.h"
#include "engine/Layout.h"
#include "engine/SceneManager.h"

namespace Game {

namespace Scene {

using namespace UI;

static const std::string k_GameVer = "v0.4";
static constexpr int k_Amount = 5;
static constexpr int k_Fontsize = 32;

static Button MainMenuButtons[k_Amount];
static bool Exit;
static auto SelectedScene = SceneManager::Scenes::Exit;
static int Hovering = 1;

static void Init() {
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
        Text = "Controls";
        break;
      case 3:
        Text = "Credits";
        break;
      case 4:
        Text = "Exit";
        break;
      default:
        Text = "NULL";
    }

    UI::CreateButton(MainMenuButtons[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

static void Unload() {
  // TODO
}

static void InputButton() {

  if (IsKeyReleased(KEY_ESCAPE)) {
    Exit = true;
  }

  UI::InputButton(MainMenuButtons, Hovering, k_Amount);

  if (IsKeyReleased(KEY_ENTER)) {
    SelectedScene = static_cast<SceneManager::Scenes>(Hovering);
    Exit = true;
  }
}

static void Draw() {

  constexpr int k_FontSizeTitle = 32;

  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Flok", (g_ScreenWidth - MeasureText("Flok", k_FontSizeTitle)) / 2, 64, k_FontSizeTitle, BLACK);

  RenderButtons(MainMenuButtons, k_Amount);

  DrawText(k_GameVer.c_str(), 10, 10, 10, BLACK);

  DrawText("Select = KeyUp / KeyDown", 10, g_ScreenHeight - 40, 10, BLACK);
  DrawText("Enter = Enter", 10, g_ScreenHeight - 30, 10, BLACK);
  DrawText("Exit = Escape", 10, g_ScreenHeight - 20, 10, BLACK);

  EndDrawing();
}

void Menu() {
  Init();

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Draw();
  }

  Unload();
  ChangeScene(SelectedScene);
}

} // namespace Scene
} // namespace Game

#include "MainMenu.h"

#include <array>
#include <string>

#include "raylib.h"

#include "Constants.h"
#include "engine/Buttons.h"
#include "engine/Layout.h"
#include "engine/SceneManager.h"

namespace {

using namespace Buttons;

constexpr int k_Amount = 3;
constexpr int k_Fontsize = 32;

Button MainMenuButtons[k_Amount];
bool Exit;
auto SelectedScene = SceneManager::Scenes::Exit;
int Hovering = 0;



void Init() {
  //TODO
  // Add textures and fonts and edit accordingly

  //REMOVE
  constexpr Texture2D k_Def = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};
  constexpr Font k_DefFont = {.baseSize = 0,
                              .glyphCount = 0,
                              .glyphPadding = 0,
                              .texture = k_Def,
                              .recs = nullptr,
                              .glyphs = nullptr};

  constexpr Margin k_Margin = {.f_Top = 20, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  std::string Text;
  for (int I = 0; I < k_Amount; I++) {

    switch (I) {
      case 0:
        Text = "Play";
        break;
      case 1:
        Text = "Credits";
        break;
      case 2:
        Text = "Exit";
        break;
      default:
        Text = "NULL";
    }

    MainMenuButtons[I] = {
        .f_BoundingBox = {.x = g_ScreenWidth / 2.0F,
                          .y = g_ScreenHeight / 2.0F + k_Margin.f_Top * static_cast<float>(I),
                          .width = static_cast<float>(MeasureText(Text.c_str(), k_Fontsize)),
                          .height = k_Fontsize},
        .f_Padding = k_Padding,
        .f_Margin = k_Padding,
        .f_Sprite = k_Def,
        .f_HoverTint = WHITE,
        .f_TextColor = WHITE,
        .f_Text = Text,
        .f_Font = k_DefFont,
        .f_FontSize = k_Fontsize,
        .f_IsHover = false,
        .f_IsTextCenter = true};
  }
}



void Unload() {
  // TODO
}



void Input() {
  Buttons::Input(MainMenuButtons, Hovering, k_Amount);
}



void Update() {
  SelectedScene = static_cast<SceneManager::Scenes>(Hovering);
}



void Draw() {

  constexpr int k_FontSizeTitle = 32;

  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Flok", (g_ScreenWidth - MeasureText("Flok", k_FontSizeTitle)) / 2, 64, k_FontSizeTitle, BLACK);

  RenderButtons(MainMenuButtons, Hovering);

  EndDrawing();
}


}



void MainMenu::Menu() {
  Init();

  while (!Exit && !WindowShouldClose()) {
    Input();
    Update();
    Draw();
  }

  Unload();
  ChangeScene(SelectedScene);
}

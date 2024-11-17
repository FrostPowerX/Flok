#include "Credits.h"

#include "Constants.h"
#include "actors/PlayerClass.h"
#include "engine/Collisions.h"
#include "engine/SceneManager.h"

namespace Game {

namespace Scene {

struct Text {
  std::string f_Text;
  int f_X;
  int f_Y;
  int f_FontSize;
  Color f_Color;
};

static const int k_MaxTexts = 5;

static Text f_Texts[k_MaxTexts];

static bool Exit = false;

static void InitTexts() {
  f_Texts[0].f_Text = "Made by Nicolas Gallardo";
  f_Texts[0].f_Y = 140;

  f_Texts[1].f_Text = "\t Collaborate Emanuel Parajon";
  f_Texts[1].f_Y = 160;

  f_Texts[2].f_Text = "Art by Eduardo Scarpato (https://im-dagon.itch.io/)";
  f_Texts[2].f_Y = 200;

  f_Texts[3].f_Text = "\t Toxic Frog https://tinyurl.com/toxic-frog";
  f_Texts[3].f_Y = 260;

  f_Texts[4].f_Text = "\t Forest Tileset https://tinyurl.com/ForestTitleSet";
  f_Texts[4].f_Y = 320;

  for (int i = 0; i < k_MaxTexts; i++) {
    f_Texts[i].f_X = 100;
    f_Texts[i].f_FontSize = 20;
    f_Texts[i].f_Color = BLACK;
  }
}

static void Init() {

  ShowCursor();
  InitTexts();
}

static bool IsMouseOnText(int X, int Y, int k_Fontsize, std::string Text) {

  Rectangle f_Text;
  f_Text.x = X;
  f_Text.y = Y;
  f_Text.width = MeasureText(Text.c_str(), k_Fontsize);
  f_Text.height = k_Fontsize;

  return Collisions::IsRectMouse(f_Text);
}

static void InputButton() {
  if (IsKeyReleased(KEY_ESCAPE)) {
    Exit = true;
  }

  for (int I = 0; I < k_MaxTexts; I++) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        IsMouseOnText(f_Texts[I].f_X, f_Texts[I].f_Y, f_Texts[I].f_FontSize, f_Texts[I].f_Text)) {
      switch (I) {
        case 0:
          OpenURL("https://projectbifron.itch.io/");
          break;

        case 1:
          OpenURL("https://frostpower.itch.io/");
          break;

        case 2:
          OpenURL("https://im-dagon.itch.io/");
          break;

        case 3:
          OpenURL("https://tinyurl.com/toxic-frog");
          break;

        case 4:
          OpenURL("https://tinyurl.com/ForestTitleSet");
          break;
      }
    }
  }
}

static void Draw() {
  // TODO
  // improve this
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    for (int i = 0; i < k_MaxTexts; i++) {
      DrawText(f_Texts[i].f_Text.c_str(), f_Texts[i].f_X, f_Texts[i].f_Y, f_Texts[i].f_FontSize, f_Texts[i].f_Color);
    }
  }
  EndDrawing();
}

void Credits() {

  Init();

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Draw();
  }

  HideCursor();

  Exit = false;
  ChangeScene(SceneManager::Scenes::MainMenu);
}

} // namespace Scene

} // namespace Game

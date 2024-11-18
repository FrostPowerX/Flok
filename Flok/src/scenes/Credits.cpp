#include "Credits.h"

#include "Constants.h"
#include "actors/PlayerClass.h"
#include "engine/Collisions.h"
#include "engine/Parallax.h"
#include "engine/SceneManager.h"
#include "engine/SoundManager.h"

namespace Game {

namespace Scene {

struct Text {
  std::string f_Text;
  int f_X;
  int f_Y;
  int f_FontSize;
  Color f_Color;
};

static const int k_MaxTexts = 6;

static Text f_Buttons[k_MaxTexts];

static bool Exit = false;

static void InitTexts();
static bool IsMouseOnText(int X, int Y, int k_Fontsize, std::string Text);

static void Init() {

  Parallax::RestartParallax();

  ShowCursor();
  InitTexts();
}

static void InputButton() {
  if (IsKeyReleased(KEY_ESCAPE)) {

    Game::SoundManager::PlayS("Back");
    Exit = true;
  }

  for (int I = 0; I < k_MaxTexts; I++) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        IsMouseOnText(f_Buttons[I].f_X, f_Buttons[I].f_Y, f_Buttons[I].f_FontSize, f_Buttons[I].f_Text)) {
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

        case 5:
          OpenURL("https://sfbgames.itch.io/chiptone");
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

    Parallax::DrawBackground();

    for (int i = 0; i < k_MaxTexts; i++) {
      DrawText(f_Buttons[i].f_Text.c_str(), f_Buttons[i].f_X, f_Buttons[i].f_Y, f_Buttons[i].f_FontSize,
               f_Buttons[i].f_Color);
    }

    DrawText("Back = Escape", 10, g_ScreenHeight - 30, 10, BLACK);
    DrawText("(Click on credits for more information)", 10, g_ScreenHeight - 20, 10, BLACK);
  }
  EndDrawing();
}

static void Unload() {

  HideCursor();

  Exit = false;
  ChangeScene(SceneManager::Scenes::MainMenu);
}

void Credits() {

  Init();

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Draw();
  }

  Unload();
}

static void InitTexts() {
  f_Buttons[0].f_Text = "Made by Nicolas Gallardo";
  f_Buttons[0].f_Y = 140;

  f_Buttons[1].f_Text = "\t Collaborate Emanuel Parajon";
  f_Buttons[1].f_Y = 160;

  f_Buttons[2].f_Text = "Art by Eduardo Scarpato: (https://im-dagon.itch.io/)";
  f_Buttons[2].f_Y = 200;

  f_Buttons[3].f_Text = "\t Toxic Frog: https://tinyurl.com/toxic-frog";
  f_Buttons[3].f_Y = 260;

  f_Buttons[4].f_Text = "\t Forest Tileset: https://tinyurl.com/ForestTitleSet";
  f_Buttons[4].f_Y = 320;

  f_Buttons[5].f_Text = "ChipTone: https://sfbgames.itch.io/chiptone";
  f_Buttons[5].f_Y = 380;

  for (int i = 0; i < k_MaxTexts; i++) {
    f_Buttons[i].f_X = 100;
    f_Buttons[i].f_FontSize = 20;
    f_Buttons[i].f_Color = BLACK;
  }
}

static bool IsMouseOnText(int X, int Y, int k_Fontsize, std::string Text) {

  Rectangle f_Text;
  f_Text.x = static_cast<float>(X);
  f_Text.y = static_cast<float>(Y);
  f_Text.width = static_cast<float>(MeasureText(Text.c_str(), k_Fontsize));
  f_Text.height = static_cast<float>(k_Fontsize);

  return Collisions::IsRectMouse(f_Text);
}

} // namespace Scene

} // namespace Game

#include "Play.h"

#include <list>
#include <stack>

#include "raylib.h"

#include "Constants.h"
#include "actors/PlayerClass.h"
#include "actors/WallClass.h"
#include "engine/Buttons.h"
#include "engine/Collisions.h"
#include "engine/GameManager.h"
#include "engine/Parallax.h"
#include "engine/SceneManager.h"
#include "engine/SoundManager.h"
#include "scenes/Lose.h"

namespace Game {

namespace Scene {

using namespace UI;
using namespace Actors;

static const int k_MaxButtons = 2;
static const int k_MaxWalls = 5;

static PlayerType f_Player1;
static PlayerType f_Player2;

static Button PauseMenu[k_MaxButtons];

static constexpr int k_Fontsize = 32;
static int Hovering = 1;

static constexpr float k_PlayerUpwardPush = 500.0F;
static constexpr float k_WallTimer = 5.0F;
static constexpr float k_WallSpeed = 400.0F;
static float WallTime = 0;

static bool Exit = false;
static bool f_Pause = false;
static bool Multiplayer = false;
static bool f_Menu = false;

static void WallManager(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls);
static bool CheckForPlayerWallCollision(PlayerType Player, const std::list<WallType*>& Walls);
static void CheckLoseCondition(PlayerType& Player, std::list<WallType*>& Walls);
static void CheckPointOnPassWall(PlayerType Player, std::list<WallType*>& Walls);
static void RandomPointSound();
static void OpenRandomURL();

static void Init() {
  Hovering = 1;
  f_Menu = false;

  SoundManager::StopM("Menu");
  SoundManager::PlayM("GamePlay");

  Parallax::RestartParallax();

  InitPlayer(f_Player1, "Player1");
  float x = GetBoundingBoxPlayer(f_Player1).x - GetBoundingBoxPlayer(f_Player1).width * 0.5f;
  SetPositionPlayer(f_Player1, x, GetBoundingBoxPlayer(f_Player1).y);

  if (Multiplayer) {

    InitPlayer(f_Player2, "Player2");
    x = GetBoundingBoxPlayer(f_Player2).x + GetBoundingBoxPlayer(f_Player2).width * 0.5f;
    SetPositionPlayer(f_Player2, x, GetBoundingBoxPlayer(f_Player2).y);
  }

  constexpr Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < k_MaxButtons; I++) {

    switch (I) {
      case 0:
        Text = "Continue";
        break;
      case 1:
        Text = "Menu";
    }

    UI::CreateButton(PauseMenu[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

static void InputButton() {

  if (IsKeyPressed(KEY_ESCAPE)) {

    (f_Pause) ? Game::SoundManager::PlayS("UnPause") : Game::SoundManager::PlayS("Pause");
    f_Pause = !f_Pause;
  }

  if (f_Pause) {
    UI::InputButton(PauseMenu, Hovering, k_MaxButtons);

    if (IsKeyReleased(KEY_ENTER)) {

      Game::SoundManager::PlayS("Enter");
      switch (Hovering) {

        case 1:
          f_Pause = !f_Pause;
          break;

        case 2:
          Exit = true;
          f_Menu = true;
          f_Pause = !f_Pause;
          break;
      }
    }

  } else {
    if (IsKeyPressed(KEY_SPACE)) {

      AddJump(Multiplayer);
      PushPlayer(f_Player1, {0, -1}, k_PlayerUpwardPush + GetSpeedPlayer(f_Player1));
    }

    if (IsKeyPressed(KEY_UP) && Multiplayer) {

      AddJump(Multiplayer);
      PushPlayer(f_Player2, {0, -1}, k_PlayerUpwardPush + GetSpeedPlayer(f_Player2));
    }
  }
}

static void Update(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls) {

  Game::SoundManager::Update();

  if (!f_Pause) {

    Parallax::UpdateParallax(k_WallSpeed);

    UpdatePlayer(f_Player1);

    if (Multiplayer) {
      UpdatePlayer(f_Player2);
    }

    WallManager(Walls, HiddenWalls);

    CheckLoseCondition(f_Player1, Walls);

    if (Multiplayer) {
      CheckLoseCondition(f_Player2, Walls);
    }

    CheckPointOnPassWall(f_Player1, Walls);
  }
}

static void Draw(const std::list<WallType*>& Walls) {

  Parallax::DrawBackground();
  Parallax::DrawMidground();
  Parallax::DrawMidground2();

  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    for (const auto Wall : Walls) {
      if (Wall) {
        DrawWalls(*Wall);
      }
    }

    DrawPlayer(f_Player1);

    if (Multiplayer) {
      DrawPlayer(f_Player2);
    }

    const std::string k_Score = "Score: " + std::to_string(GetScore(Multiplayer));

    Parallax::DrawFrontground();

    DrawText(k_Score.c_str(), 20, 10, 20, WHITE);

    if (f_Pause) {
      DrawRectangle(0, 0, g_ScreenWidth, g_ScreenHeight, Color{0, 0, 0, 150});

      if (Multiplayer) {

        DrawText("Jump P1 = Space", 10, g_ScreenHeight - 60, 10, WHITE);
        DrawText("Jump P2 = ArrowUP", 10, g_ScreenHeight - 50, 10, WHITE);
      } else {

        DrawText("Jump = Space", 10, g_ScreenHeight - 50, 10, WHITE);
      }

      DrawText("Select = ArrowUp / ArrowDown", 10, g_ScreenHeight - 40, 10, WHITE);
      DrawText("Enter = Enter", 10, g_ScreenHeight - 30, 10, WHITE);
      DrawText("Pause/Despause = Escape", 10, g_ScreenHeight - 20, 10, WHITE);

      RenderButtons(PauseMenu, k_MaxButtons);
    }
  }
  EndDrawing();
}

static void Unload() {

  Exit = false;

  UnloadGManager();
}

void Play(const bool k_MultiP) {
  // BUG:
  //  it feels awful and the collision is very imprecise

  std::list<WallType*> Walls;
  std::stack<WallType*> HiddenWalls;

  Multiplayer = k_MultiP;

  Init();

  while (!Exit && !WindowShouldClose()) {
    InputButton();
    Update(Walls, HiddenWalls);
    Draw(Walls);
  }

  for (const auto Wall : Walls) {
    delete Wall;
  }
  for (size_t I = 0; I < HiddenWalls.size(); I++) {
    delete HiddenWalls.top();
    HiddenWalls.pop();
  }

  Unload();

  if (f_Menu) {

    ResetScore(Multiplayer);
    SceneManager::ChangeScene();
  } else {

    Lose(Multiplayer);
  }
}

static void WallManager(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls) {
  // TODO
  //  logic to manage level and speed of walls
  for (int i = 0; i < k_MaxWalls; i++) {
    WallType* NewWall = nullptr;
    WallTime += GetFrameTime();

    if (WallTime >= k_WallTimer) {
      WallTime = 0;

      if (!HiddenWalls.empty()) {
        NewWall = HiddenWalls.top();
        HiddenWalls.pop();
      } else {
        NewWall = new WallType(MakeWall(k_WallSpeed / k_MaxWalls));
      }
    }

    for (auto& Wall : Walls) {

      if (NewWall && !Wall) {
        Wall = NewWall;
        Wall->f_IsHidden = false;
        NewWall = nullptr;
      } else {
        if (Wall && Wall->f_Position <= -Wall->f_WallWidth) {
          ResetWall(*Wall, k_WallSpeed / k_MaxWalls);
          HiddenWalls.push(Wall);
          Wall = nullptr;
        } else if (Wall) {
          UpdateWalls(*Wall);
        }
      }
    }

    if (NewWall) {
      Walls.push_back(NewWall);
    }
  }
}

static bool CheckForPlayerWallCollision(PlayerType Player, const std::list<WallType*>& Walls) {

  bool Collided = false;

  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle const Bb = GetBoundingBoxPlayer(Player);
      Collided = Collisions::IsRectRect(
                     Bb, {.x = Wall->f_Position, .y = 0, .width = Wall->f_WallWidth, .height = Wall->f_GapStart}) ||
                 Collisions::IsRectRect(Bb, {.x = Wall->f_Position,
                                             .y = Wall->f_GapStart + Wall->f_GapSize,
                                             .width = Wall->f_WallWidth,
                                             .height = g_ScreenHeight - (Wall->f_GapStart + Wall->f_GapSize)});
      if (Collided)
        return Collided;
    }
  }

  return Collided;
}

static void CheckLoseCondition(PlayerType& Player, std::list<WallType*>& Walls) {

  bool HitsWall = CheckForPlayerWallCollision(Player, Walls);
  bool HitsBorder = Collisions::IsRectBorder(GetBoundingBoxPlayer(Player));

  // in case it hits roof
  if (HitsBorder) {
    if (GetBoundingBoxPlayer(Player).y < GetBoundingBoxPlayer(Player).height) {
      MovePlayer(Player, abs(GetBoundingBoxPlayer(Player).y * 2));
    } else {

      Game::SoundManager::PlayS("Fall");

#ifdef _NDEBUG
      OpenRandomURL();
#endif

      AddLose(Multiplayer);
      Exit = true;
    }
  } else if (HitsWall) {

    Game::SoundManager::PlayS("Crash");
    AddLose(Multiplayer);
    Exit = true;
  }
}

static void CheckPointOnPassWall(PlayerType Player, std::list<WallType*>& Walls) {

  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle const Bb = GetBoundingBoxPlayer(Player);

      if (!Wall->f_checked) {

        if (Wall->f_Position < Bb.x) {

          RandomPointSound();
          AddScore(Multiplayer);
          Wall->f_checked = true;
        }
      }
    }
  }
}

static void RandomPointSound() {

  int Rand = GetRandomValue(1, 3);

  std::string soundName = "Point" + std::to_string(Rand);

  Game::SoundManager::PlayS(soundName);
}

void OpenRandomURL() {

  int random = GetRandomValue(1, 10);
  std::string url = "";

  switch (random) {
    case 1:
      url = "https://www.google.com/"
            "search?q=ayuda+accidentalmente+arme+una+estanter%C3%ADa&sca_esv=9844c5af186a16ef&sxsrf="
            "ADLYWIKdF4tliTEh6f6as2aYvh96I6rR9Q%3A1732070220287&ei=TEs9Z-2XEY3T1sQP2ef6sAY&oq=ayuda+ac&gs_lp="
            "Egxnd3Mtd2l6LXNlcnAiCGF5dWRhIGFjKgIIADIKEAAYgAQYQxiKBTIKEAAYgAQYQxiKBTIKEAAYgAQYQxiKBTIFEAAYgAQyBRAAGIAEMg"
            "UQABiABDIFEAAYgAQyBRAAGIAEMgUQABiABDIFEAAYgARI1EdQlh5Y_"
            "SZwAXgBkAEAmAFroAGVBqoBAzQuNLgBA8gBAPgBAZgCCaACvQbCAgoQABiwAxjWBBhHwgIKECMYgAQYJxiKBcICBBAjGCfCAg4QABiABBi"
            "xAxiDARiKBcICERAuGIAEGLEDGNEDGIMBGMcBwgILEAAYgAQYsQMYgwHCAgsQLhiABBixAxiDAcICChAuGIAEGEMYigXCAggQLhiABBixA"
            "8ICCBAAGIAEGLEDwgILEC4YgAQYxwEYrwGYAwCIBgGQBgiSBwMzLjagB-1Q&sclient=gws-wiz-serp";
      break;

    case 2:
      url = "https://www.youtube.com/watch?v=lqZsRqOjmMM";
      break;

    case 3:
      url = "https://www.youtube.com/watch?v=F4pzRMioFnc";
      break;

    case 4:
      url = "https://i.chzbgr.com/full/9876357376/h8B43EDFA/zelda-as-girl-made-with-mematic-zelda-fans-zelda";
      break;

    case 5:
      url = "https://www.youtube.com/shorts/pvtTD1NiXiA";
      break;

    case 6:
      url = "https://www.youtube.com/watch?v=i29t-5tEp_o&list=PL1zuqabrVlPu09hsd9ANXCJCwIjone1mM";
      break;

    case 7:
      url = "https://www.youtube.com/shorts/X6JBeKkyD84";
      break;

    case 8:
      url = "https://www.youtube.com/watch?v=XyuR-x5PMcU";
      break;

    case 9:
      url = "https://www.youtube.com/watch?v=DHfRfU3XUEo";
      break;

    case 10:
      url = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
      break;
  }

  OpenURL(url.c_str());
}

} // namespace Scene
} // namespace Game

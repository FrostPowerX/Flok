﻿#include "Play.h"

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

static bool Exit = false;
static constexpr float k_PlayerUpwardPush = 500.0F;
static constexpr float k_WallTimer = 5.0F;
static constexpr float k_WallSpeed = 400.0F;
static float WallTime = 0;

static bool Pause = false;
static bool Multiplayer = false;

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

static void Init() {
  Hovering = 1;

  Parallax::InitParallax();

  InitPlayer(f_Player1, "res/ToxicFrog/BlueBlue/ToxicFrogBlueBlue_Hop.png");
  float x = GetBoundingBoxPlayer(f_Player1).x - GetBoundingBoxPlayer(f_Player1).width * 0.5f;
  SetPositionPlayer(f_Player1, x, GetBoundingBoxPlayer(f_Player1).y);

  if (Multiplayer) {

    InitPlayer(f_Player2, "res/ToxicFrog/GreenBlue/ToxicFrogGreenBlue_Hop.png");
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

  if (IsKeyPressed(KEY_ESCAPE))
    Pause = !Pause;

  if (Pause) {
    UI::InputButton(PauseMenu, Hovering, k_MaxButtons);

    if (IsKeyReleased(KEY_ENTER)) {
      switch (Hovering) {

        case 1:
          Pause = !Pause;
          break;

        case 2:
          Exit = true;
          Pause = !Pause;
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

static void CheckLoseCondition(PlayerType Player, std::list<WallType*>& Walls) {

  bool HitsWall = CheckForPlayerWallCollision(Player, Walls);
  bool HitsBorder = Collisions::IsRectBorder(GetBoundingBoxPlayer(Player));

  // in case it hits roof
  if (HitsBorder) {
    if (GetBoundingBoxPlayer(Player).y < GetBoundingBoxPlayer(Player).height) {
      MovePlayer(Player, 10);
    } else {

      AddLose(Multiplayer);
      Exit = true;
    }
  } else if (HitsWall) {

    AddLose(Multiplayer);
    Exit = true;
  }
}

static void CheckPointOnPassWall(PlayerType Player, std::list<WallType*>& Walls) {

  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle const Bb = GetBoundingBoxPlayer(Player);

      if (!Wall->f_checked) {

        if (Wall->f_Position < Bb.y) {

          AddScore();
          Wall->f_checked = true;
        }
      }
    }
  }
}

static void Update(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls) {

  if (!Pause) {

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

    if (Pause)
      RenderButtons(PauseMenu, k_MaxButtons);

    Parallax::DrawFrontground();
  }
  EndDrawing();
}

static void Unload() {

  Exit = false;

  UnloadPlayer(f_Player1);

  if (Multiplayer) {
    UnloadPlayer(f_Player2);
  }

  ResetScore(Multiplayer);
  UnloadGManager();

  Parallax::UnloadParallax();
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

  ChangeScene(SceneManager::Scenes::MainMenu);
}

} // namespace Scene
} // namespace Game

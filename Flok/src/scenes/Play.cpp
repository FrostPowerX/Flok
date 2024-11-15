#include "Play.h"

#include <list>
#include <stack>

#include "raylib.h"

#include "Constants.h"
#include "actors/PlayerClass.h"
#include "actors/WallClass.h"
#include "engine/Buttons.h"
#include "engine/Collisions.h"
#include "engine/Parallax.h"
#include "engine/SceneManager.h"

namespace game {

namespace scenes {

using namespace Buttons;
using namespace Actors;

const int k_maxButtons = 2;

PlayerType f_Player1;

Button PauseMenu[k_maxButtons];

constexpr int k_Fontsize = 32;
int Hovering = 1;

bool Exit = false;
constexpr float k_PlayerUpwardPush = 500.0F;
constexpr float k_WallTimer = 3.0F;
constexpr float k_WallSpeed = 400.0F;
float WallTime = 0;

bool Pause = false;

void WallManager(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls) {
  // TODO
  //  logic to manage level and speed of walls

  WallType* NewWall = nullptr;
  WallTime += GetFrameTime();

  if (WallTime >= k_WallTimer) {
    WallTime = 0;

    if (!HiddenWalls.empty()) {
      NewWall = HiddenWalls.top();
      HiddenWalls.pop();
    } else {
      NewWall = new WallType(MakeWall(k_WallSpeed));
    }
  }

  for (auto& Wall : Walls) {

    if (NewWall && !Wall) {
      Wall = NewWall;
      Wall->f_IsHidden = false;
      NewWall = nullptr;
    } else {
      if (Wall && Wall->f_Position <= -Wall->f_WallWidth) {
        ResetWall(*Wall, k_WallSpeed);
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

void Init() {
  Hovering = 1;

  Parallax::InitParallax();

  constexpr Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < k_maxButtons; I++) {

    switch (I) {
      case 0:
        Text = "Continue";
        break;
      case 1:
        Text = "Menu";
    }

    Buttons::Create(PauseMenu[I], Text, k_Margin, k_Padding, k_Fontsize, I);
  }
}

void Input() {

  if (IsKeyPressed(KEY_ESCAPE))
    Pause = !Pause;

  if (Pause) {
    Buttons::Input(PauseMenu, Hovering, k_maxButtons);

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
      PushPlayer(f_Player1, {0, -1}, k_PlayerUpwardPush + GetSpeedPlayer(f_Player1));
    }
  }
}

bool CheckForPlayerWallCollision(const std::list<WallType*>& Walls) {
  bool Collided = false;
  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle const Bb = GetBoundingBoxPlayer(f_Player1);
      Collided = Collisions::IsRectRect(
                     Bb, {.x = Wall->f_Position, .y = 0, .width = Wall->f_WallWidth, .height = Wall->f_GapStart}) ||
                 Collisions::IsRectRect(Bb, {.x = Wall->f_Position,
                                             .y = Wall->f_GapStart + Wall->f_GapSize,
                                             .width = Wall->f_WallWidth,
                                             .height = g_ScreenHeight - (Wall->f_GapStart + Wall->f_GapSize)});
    }
  }
  return Collided;
}

void CheckLoseCondition(PlayerType Player, std::list<WallType*>& Walls) {

  bool HitsWall = CheckForPlayerWallCollision(Walls);
  bool HitsBorder = Collisions::IsRectBorder(GetBoundingBoxPlayer(Player));

  // in case it hits roof
  if (HitsBorder) {
    if (GetBoundingBoxPlayer(Player).y < GetBoundingBoxPlayer(Player).height) {
      MovePlayer(Player, 10);
    } else {
      Exit = true;
    }
  } else if (HitsWall) {
    Exit = true;
  }
}

void Update(std::list<WallType*>& Walls, std::stack<WallType*>& HiddenWalls) {

  if (!Pause) {

    Parallax::UpdateParallax(k_WallSpeed);

    UpdatePlayer(f_Player1);
    WallManager(Walls, HiddenWalls);

    CheckLoseCondition(f_Player1, Walls);
  }
}

void Draw(const std::list<WallType*>& Walls) {

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
  }

  if (Pause)
    RenderButtons(PauseMenu, k_maxButtons);

  Parallax::DrawFrontground();

  EndDrawing();
}

void Unload() {
  Exit = false;
  UnloadPlayer(f_Player1);
  Parallax::UnloadParallax();
}

void Play() {
  // BUG:
  //  it feels awful and the collision is very imprecise

  std::list<WallType*> Walls;
  std::stack<WallType*> HiddenWalls;

  Init();
  InitPlayer(f_Player1, "res/ToxicFrog/BlueBlue/ToxicFrogBlueBlue_Hop.png");

  while (!Exit && !WindowShouldClose()) {
    Input();
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

} // namespace scenes
} // namespace game

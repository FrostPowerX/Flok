﻿#include "Play.h"

#include <list>
#include <stack>

#include "Constants.h"
#include "raylib.h"
#include "actors/PlayerClass.h"
#include "actors/WallClass.h"
#include "engine/Collisions.h"

namespace {

constexpr float k_GameVer = 0.1F;

bool Exit = false;
constexpr float k_PlayerUpwardPush = 300.0F;
constexpr float k_WallTimer = 3.0F;
constexpr float k_WallSpeed = 800.0F;
float WallTime = 0;



void WallManager(std::list<Wall::WallType*>& Walls,
                 std::stack<Wall::WallType*>& HiddenWalls) {
  //todo logic to manage level and speed of walls

  Wall::WallType* NewWall = nullptr;

  WallTime += GetFrameTime();

  if (WallTime >= k_WallTimer) {
    WallTime = 0;

    if (!HiddenWalls.empty()) {
      NewWall = HiddenWalls.top();
      HiddenWalls.pop();
    } else {
      NewWall = new Wall::WallType(Wall::Make(k_WallSpeed));
    }

  }

  for (auto& Wall : Walls) {

    if (NewWall && !Wall) {
      Wall = NewWall;
      Wall->f_IsHidden = false;
      //exhaust NewWall*
      NewWall = nullptr;
    } else {
      if (Wall && Wall->f_Position <= -Wall->f_WallWidth) {
        Reset(*Wall, k_WallSpeed);
        HiddenWalls.push(Wall);
        Wall = nullptr;
      } else if (Wall) {
        Update(*Wall);
      }
    }
  }

  if (NewWall) {
    Walls.push_back(NewWall);
  }
}



void Input() {
  /*if (IsKeyPressed(KEY_SPACE)) {
    PlayerClass::Push({0,-1}, k_PlayerUpwardPush);
  }*/
  if (IsKeyPressed(KEY_W)) {
    PlayerClass::Push({0, -1}, k_PlayerUpwardPush);
  } else if (IsKeyPressed(KEY_S)) {
    PlayerClass::Push({0, 1}, k_PlayerUpwardPush);
  }
}



bool CheckForPlayerWallCollision(const std::list<Wall::WallType*>& Walls) {
  bool Collided = false;
  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle Bb = PlayerClass::GetBoundingBox();
      Collided = Collisions::IsAABB(Bb,
                                    {.x = Wall->f_Position,
                                     .y = 0,
                                     .width = Wall->f_WallWidth,
                                     .height = Wall->f_GapStart}) ||
                 Collisions::IsAABB(Bb,
                                    {.x = Wall->f_Position,
                                     .y = Wall->f_GapStart + Wall->f_GapSize,
                                     .width = Wall->f_WallWidth,
                                     .height = g_ScreenHeight - (Wall->f_GapStart + Wall->f_GapSize)});
    }
  }
  return Collided;
}



bool Update(std::list<Wall::WallType*>& Walls,
            std::stack<Wall::WallType*>& HiddenWalls) {
  PlayerClass::Update();
  WallManager(Walls, HiddenWalls);
  return CheckForPlayerWallCollision(Walls);
}



void Draw(const std::list<Wall::WallType*>& Walls) {
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    for (const auto Wall : Walls) {
      if (Wall) {
        Wall::Draw(*Wall);
      }
    }

    PlayerClass::Draw();

    DrawText(TextFormat("v%.1f", k_GameVer), 10, 10, 10, BLACK);
  }
  EndDrawing();
}

}



void Play::Play() {

  std::list<Wall::WallType*> Walls;
  std::stack<Wall::WallType*> HiddenWalls;

  PlayerClass::Init();

  while (!Exit && !WindowShouldClose()) {
    Input();
    Exit = Update(Walls, HiddenWalls);
    Draw(Walls);
  }
}

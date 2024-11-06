#include "Play.h"

#include "raylib.h"
#include "actors/PlayerClass.h"

namespace  {

bool Exit = false;
constexpr float k_PlayerUpwardPush = 300.0F;

void Input() {
  /*if (IsKeyPressed(KEY_SPACE)) {
    PlayerClass::Push({0,-1}, k_PlayerUpwardPush);
  }*/
  if (IsKeyPressed(KEY_W)) {
    PlayerClass::Push({0,-1}, k_PlayerUpwardPush);
  } else if (IsKeyPressed(KEY_S)) {
    PlayerClass::Push({0,1}, k_PlayerUpwardPush);
  }
}

void Update() {
  PlayerClass::Update();
}

void Draw() {
  BeginDrawing();
  {
    ClearBackground(RAYWHITE);
    PlayerClass::Draw();
  }
  EndDrawing();
}

}

void Play::Play() {

  PlayerClass::Init();

  while(!Exit && !WindowShouldClose()) {
    Input();
    Update();
    Draw();
  }
}

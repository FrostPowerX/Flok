#include "Play.h"

#include "raylib.h"
#include "actors/PlayerClass.h"

namespace  {

bool Exit = false;
constexpr float k_PlayerUpwardPush = 300.0F;

void Input() {
  
}

void Update() {
  
}

void Draw() {
  
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

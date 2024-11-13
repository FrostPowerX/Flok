#include "Play.h"

#include <list>
#include <stack>

#include "raylib.h"

#include "Constants.h"
#include "actors/PlayerClass.h"
#include "actors/WallClass.h"
#include "engine/Buttons.h"
#include "engine/Collisions.h"
#include "engine/SceneManager.h"

namespace {

using namespace Buttons;

const int maxButtons = 2;

Texture2D backGround;
Texture2D midGround;
Texture2D midGround2;
Texture2D frontGround;

Button pauseMenu[maxButtons];

constexpr int k_Fontsize = 32;
int Hovering = 1;

float k_Scrollingback = 0.0f;
float k_Scrollingmid = 0.0f;
float k_Scrollingmid2 = 0.0f;
float k_Scrollingfront = 0.0f;

bool Exit = false;
constexpr float k_PlayerUpwardPush = 500.0F;
constexpr float k_WallTimer = 3.0F;
constexpr float k_WallSpeed = 400.0F;
float WallTime = 0;

bool pause = false;

void WallManager(std::list<Wall::WallType*>& Walls, std::stack<Wall::WallType*>& HiddenWalls) {
  // TODO
  //  logic to manage level and speed of walls

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
      // exhaust NewWall*
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

void Init() {
  Hovering = 1;

  backGround = LoadTexture("res/JungleTileset/ParallaxBackground/Back.png");
  midGround = LoadTexture("res/JungleTileset/ParallaxBackground/Back2.png");
  midGround2 = LoadTexture("res/JungleTileset/ParallaxBackground/Back3.png");
  frontGround = LoadTexture("res/JungleTileset/ParallaxBackground/BushFront.png");

  backGround.height = g_ScreenHeight;
  backGround.width = g_ScreenWidth;

  midGround.height = g_ScreenHeight;
  midGround.width = g_ScreenWidth;

  midGround2.height = g_ScreenHeight;
  midGround2.width = g_ScreenWidth;

  frontGround.height = g_ScreenHeight;
  frontGround.width = g_ScreenWidth;

  constexpr Texture2D k_Def = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};
  constexpr Font k_DefFont = {
      .baseSize = 0, .glyphCount = 0, .glyphPadding = 0, .texture = k_Def, .recs = nullptr, .glyphs = nullptr};

  constexpr Margin k_Margin = {.f_Top = 40, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};
  constexpr Padding k_Padding = {.f_Top = 10, .f_Bottom = 0, .f_Left = 0, .f_Right = 0};

  std::string Text;

  for (int I = 0; I < maxButtons; I++) {

    switch (I) {
      case 0:
        Text = "Continue";
        break;
      case 1:
        Text = "Menu";
    }

    pauseMenu[I] = {
        .f_BoundingBox = {.x = (g_ScreenWidth - static_cast<float>(MeasureText(Text.c_str(), k_Fontsize))) / 2.0F,
                          .y = g_ScreenHeight / 2.0F + k_Margin.f_Top * static_cast<float>(I + 1),
                          .width = static_cast<float>(MeasureText(Text.c_str(), k_Fontsize)) + k_Padding.f_Top,
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

void Input() {

  if (IsKeyPressed(KEY_ESCAPE))
    pause = !pause;

  if (pause) {
    Buttons::Input(pauseMenu, Hovering, maxButtons);

    if (IsKeyReleased(KEY_ENTER)) {
      switch (Hovering) {

        case 1:
          pause = !pause;
          break;

        case 2:
          Exit = true;
          pause = !pause;
          break;
      }
    }

  } else {
    if (IsKeyPressed(KEY_SPACE)) {
       PlayerClass::Push({0, -1}, k_PlayerUpwardPush + PlayerClass::GetSpeed());
    }
  }
}

bool CheckForPlayerWallCollision(const std::list<Wall::WallType*>& Walls) {
  bool Collided = false;
  for (const auto Wall : Walls) {
    if (Wall) {
      Rectangle const Bb = PlayerClass::GetBoundingBox();
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

void Update(std::list<Wall::WallType*>& Walls, std::stack<Wall::WallType*>& HiddenWalls) {

  if (!pause) {

    bool HitsBorder = false;
    bool HitsWall = false;

    k_Scrollingback -= 0.0f;
    k_Scrollingmid -= k_WallSpeed * 0.25f * GetFrameTime();
    k_Scrollingmid2 -= k_WallSpeed * 0.5f * GetFrameTime();
    k_Scrollingfront -= k_WallSpeed * GetFrameTime();

    if (k_Scrollingback <= -backGround.width)
      k_Scrollingback = 0;
    if (k_Scrollingmid <= -midGround.width)
      k_Scrollingmid = 0;
    if (k_Scrollingmid2 <= -midGround2.width)
      k_Scrollingmid2 = 0;
    if (k_Scrollingfront <= -frontGround.width)
      k_Scrollingfront = 0;

    PlayerClass::Update();
    WallManager(Walls, HiddenWalls);

    HitsWall = CheckForPlayerWallCollision(Walls);
    HitsBorder = Collisions::IsRectBorder(PlayerClass::GetBoundingBox());

    // in case it hits roof
    if (HitsBorder) {
      if (PlayerClass::GetBoundingBox().y < PlayerClass::GetBoundingBox().height) {
        PlayerClass::MovePlayer(10);
      } else {
        Exit = true;
      }
    } else if (HitsWall) {
      Exit = true;
    }
  }
}

void Draw(const std::list<Wall::WallType*>& Walls) {
  DrawTextureEx(backGround, Vector2(k_Scrollingback, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(backGround, Vector2(backGround.width + k_Scrollingback, 0), 0.0f, 1.0f, WHITE);

  DrawTextureEx(midGround, Vector2(k_Scrollingmid, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(midGround, Vector2(midGround.width + k_Scrollingmid, 0), 0.0f, 1.0f, WHITE);

  DrawTextureEx(midGround2, Vector2(k_Scrollingmid2, 0), 0.0f, 1.0f, WHITE);
  DrawTextureEx(midGround2, Vector2{midGround2.width + k_Scrollingmid2, 0}, 0.0f, 1.0f, WHITE);

  BeginDrawing();
  {
    ClearBackground(RAYWHITE);

    for (const auto Wall : Walls) {
      if (Wall) {
        Wall::Draw(*Wall);
      }
    }

    PlayerClass::Draw();

    DrawTextureEx(frontGround, Vector2(k_Scrollingfront, 0), 0.0f, 1.0f, WHITE);
    DrawTextureEx(frontGround, Vector2(frontGround.width + k_Scrollingfront, 0), 0.0f, 1.0f, WHITE);
  }

  if (pause)
    RenderButtons(pauseMenu, maxButtons);

  EndDrawing();
}

} // namespace

void DeInit() {
  Exit = false;
  PlayerClass::Unload();

  UnloadTexture(backGround);
  UnloadTexture(midGround);
  UnloadTexture(midGround2);
  UnloadTexture(frontGround);
}

void Play::Play() {
  // BUG:
  //  it feels awful and the collision is very imprecise

  std::list<Wall::WallType*> Walls;
  std::stack<Wall::WallType*> HiddenWalls;

  Init();
  PlayerClass::Init();

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

  DeInit();

  ChangeScene(SceneManager::Scenes::MainMenu);
}

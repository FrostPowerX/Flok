#include "Buttons.h"

#include "Constants.h"
#include "SoundManager.h"

namespace UI {

void CreateButton(Button& f_Button, std::string Text, Margin k_Margin, Padding k_Padding, int k_Fontsize, int Index) {

  Texture2D k_Def = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};

  Font k_DefFont = {
      .baseSize = 0, .glyphCount = 0, .glyphPadding = 0, .texture = k_Def, .recs = nullptr, .glyphs = nullptr};

  Rectangle k_Box;

  k_Box.x = (g_ScreenWidth - static_cast<float>(MeasureText(Text.c_str(), k_Fontsize))) / 2.0F;
  k_Box.y = g_ScreenHeight / 2.0F + k_Margin.f_Top * static_cast<float>(Index + 1);

  k_Box.width = static_cast<float>(MeasureText(Text.c_str(), k_Fontsize)) + k_Padding.f_Top;
  k_Box.height = static_cast<float>(k_Fontsize);

  f_Button = {.f_BoundingBox = k_Box,
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

void RenderButtons(Button Buttons[], const int Amount) {

  for (int I = 0; I < Amount; I++) {

    // DrawTexturePro()
    if (Buttons[I].f_IsHover) {
      DrawRectangleRec(Buttons[I].f_BoundingBox, RED);
    } else {
      DrawRectangleRec(Buttons[I].f_BoundingBox, BLACK);
    }

    float k_ButtonBoxX = Buttons[I].f_BoundingBox.x + Buttons[I].f_Padding.f_Left + Buttons[I].f_BoundingBox.width / 2;
    float k_ButtonTextX = Buttons[I].f_IsTextCenter
                              ? static_cast<float>(MeasureText(Buttons[I].f_Text.c_str(), Buttons[I].f_FontSize)) / 2.0F
                              : 0;

    float k_ButtonBoxY = Buttons[I].f_BoundingBox.y + Buttons[I].f_Padding.f_Top + Buttons[I].f_BoundingBox.height / 2;
    float k_ButtonTextY =
        Buttons[I].f_Margin.f_Top - (Buttons[I].f_IsTextCenter ? static_cast<float>(Buttons[I].f_FontSize) : 0);

    int k_PosX = static_cast<int>(k_ButtonBoxX - k_ButtonTextX);
    int k_PosY = static_cast<int>(k_ButtonBoxY + k_ButtonTextY);

    // DrawTextPro();
    DrawText(Buttons[I].f_Text.c_str(), k_PosX, k_PosY, Buttons[I].f_FontSize, Buttons[I].f_TextColor);
  }
}

void InputButton(Button Buttons[], int& Hovering, const int Amount) {

  Buttons[Hovering - 1].f_IsHover = false;

  if (IsKeyReleased(KEY_DOWN)) {

    Game::SoundManager::PlayS("Select");

    if (Hovering == Amount) {
      Hovering = 1;
    } else {
      Hovering++;
    }
  } else if (IsKeyReleased(KEY_UP)) {

    Game::SoundManager::PlayS("Select");

    if (Hovering == 1) {
      Hovering = Amount;
    } else {
      Hovering--;
    }
  }

  Buttons[Hovering - 1].f_IsHover = true;
}

} // namespace UI

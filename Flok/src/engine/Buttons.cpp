#include "Buttons.h"

#include "Constants.h"

namespace UI {

void CreateButton(Button& f_Button, std::string Text, Margin k_Margin, Padding k_Padding, int k_Fontsize, int Index) {

  Texture2D k_Def = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};

  Font k_DefFont = {.baseSize = 0, .glyphCount = 0, .glyphPadding = 0, .texture = k_Def, .recs = nullptr, .glyphs = nullptr};

  f_Button = {.f_BoundingBox = {.x = (g_ScreenWidth - static_cast<float>(MeasureText(Text.c_str(), k_Fontsize))) / 2.0F,
              .y = g_ScreenHeight / 2.0F + k_Margin.f_Top * static_cast<float>(Index + 1),
              .width = static_cast<float>(MeasureText(Text.c_str(), k_Fontsize)) + k_Padding.f_Top,
              .height = static_cast<float>(k_Fontsize)},
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

void RenderButtons(Button UI[], const int Amount) {

  for (int I = 0; I < Amount; I++) {

    // DrawTexturePro()
    if (UI[I].f_IsHover) {
      DrawRectangleRec(UI[I].f_BoundingBox, RED);
    } else {
      DrawRectangleRec(UI[I].f_BoundingBox, BLACK);
    }

    float f_ButtonBoxX = UI[I].f_BoundingBox.x + UI[I].f_Padding.f_Left + UI[I].f_BoundingBox.width / 2;
    float f_ButtonTextX = UI[I].f_IsTextCenter ? static_cast<float>(MeasureText(UI[I].f_Text.c_str(), UI[I].f_FontSize)) / 2.0F : 0;

    float f_ButtonBoxY = UI[I].f_BoundingBox.y + UI[I].f_Padding.f_Top + UI[I].f_BoundingBox.height / 2;
    float f_ButtonTextY = UI[I].f_Margin.f_Top - (UI[I].f_IsTextCenter ? static_cast<float>(UI[I].f_FontSize) : 0);

    int f_PosX = static_cast<int>(f_ButtonBoxX - f_ButtonTextX);
    int f_PosY = static_cast<int>(f_ButtonBoxY + f_ButtonTextY);

    // DrawTextPro();
    DrawText(UI[I].f_Text.c_str(), f_PosX, f_PosY, UI[I].f_FontSize, UI[I].f_TextColor);
  }
}

void InputButton(Button UI[], int& Hovering, const int Amount) {

  UI[Hovering - 1].f_IsHover = false;

  if (IsKeyReleased(KEY_DOWN)) {
    if (Hovering == Amount) {
      Hovering = 1;
    } else {
      Hovering++;
    }
  } else if (IsKeyReleased(KEY_UP)) {
    if (Hovering == 1) {
      Hovering = Amount;
    } else {
      Hovering--;
    }
  }

  UI[Hovering - 1].f_IsHover = true;

}

}
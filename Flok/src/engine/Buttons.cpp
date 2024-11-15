#include "Buttons.h"

#include "Constants.h"

using namespace Buttons;

void Buttons::Create(Button& f_Button,
                      std::string Text,
                      Margin k_Margin,
                      Padding k_Padding,
                      int k_Fontsize,
                      int Index) {

  Texture2D k_Def = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};

  Font k_DefFont = {
      .baseSize = 0, .glyphCount = 0, .glyphPadding = 0, .texture = k_Def, .recs = nullptr, .glyphs = nullptr};

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

void Buttons::RenderButtons(Button Buttons[], const int Amount) {
  for (int I = 0; I < Amount; I++) {
    // DrawTexturePro()
    if (Buttons[I].f_IsHover) {
      DrawRectangleRec(Buttons[I].f_BoundingBox, DARKGRAY);
    } else {
      DrawRectangleRec(Buttons[I].f_BoundingBox, BLACK);
    }
    // DrawTextPro();

    DrawText(
        Buttons[I].f_Text.c_str(),
        static_cast<int>(Buttons[I].f_BoundingBox.x + Buttons[I].f_Padding.f_Left + Buttons[I].f_BoundingBox.width / 2 -
                         (Buttons[I].f_IsTextCenter
                              ? static_cast<float>(MeasureText(Buttons[I].f_Text.c_str(), Buttons[I].f_FontSize)) / 2.0F
                              : 0)),
        static_cast<int>(Buttons[I].f_BoundingBox.y + Buttons[I].f_Padding.f_Top + Buttons[I].f_BoundingBox.height / 2 +
                         Buttons[I].f_Margin.f_Top -
                         (Buttons[I].f_IsTextCenter ? static_cast<float>(Buttons[I].f_FontSize) : 0)),
        Buttons[I].f_FontSize, Buttons[I].f_TextColor);
  }
}

void Buttons::Input(Button Buttons[], int& Hovering, const int Amount) {
  Buttons[Hovering - 1].f_IsHover = false;

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

  Buttons[Hovering - 1].f_IsHover = true;
}

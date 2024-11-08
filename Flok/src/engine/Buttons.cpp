#include "Buttons.h"

#include "raylib.h"



void Buttons::RenderButtons(Button Buttons[], const int Amount) {
  for (int I = 0; I < Amount; I++) {
    //DrawTexturePro()
    if (Buttons[I].f_IsHover) {
      DrawRectangleRec(Buttons[I].f_BoundingBox, DARKGRAY);
    } else {
      DrawRectangleRec(Buttons[I].f_BoundingBox, BLACK);
    }
    //DrawTextPro();

    DrawText(Buttons[I].f_Text.c_str(),
             static_cast<int>(Buttons[I].f_BoundingBox.x + Buttons[I].f_Padding.f_Left + Buttons[I].f_BoundingBox.width / 2 - (
                                Buttons[I].f_IsTextCenter
                                  ? static_cast<float>(MeasureText(Buttons[I].f_Text.c_str(), Buttons[I].f_FontSize)) /
                                    2.0F
                                  : 0)),
             static_cast<int>(Buttons[I].f_BoundingBox.y + Buttons[I].f_Padding.f_Top + Buttons[I].f_BoundingBox.height / 2 + Buttons[I].f_Margin.f_Top - (Buttons[I].f_IsTextCenter
                                  ? static_cast<float>(Buttons[I].f_FontSize)
                                  : 0)), Buttons[I].f_FontSize, Buttons[I].f_TextColor);

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

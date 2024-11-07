#include "Buttons.h"



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
             static_cast<int>(Buttons[I].f_BoundingBox.x + Buttons[I].f_Padding.
                              f_Left),
             static_cast<int>(Buttons[I].f_BoundingBox.y + Buttons[I].f_Padding.
                              f_Top), Buttons[I].f_FontSize, WHITE);
  }
}



void Buttons::Input(Button Buttons[], int& Hovering, const int Amount) {
  Buttons[Hovering].f_IsHover = false;

  if (IsKeyReleased(KEY_DOWN)) {
    if (Hovering == Amount - 1) {
      Hovering = 0;
    } else {
      Hovering++;
    }
  } else if (IsKeyReleased(KEY_UP)) {
    if (Hovering == 0) {
      Hovering = Amount - 1;
    } else {
      Hovering--;
    }
  }

  Buttons[Hovering].f_IsHover = true;
}

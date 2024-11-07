#pragma once
#include <raylib.h>
#include <string>

#include "Layout.h"

namespace Buttons {

using namespace Layout;



struct Button {
  Rectangle f_BoundingBox;
  Padding f_Padding;
  Margin f_Margin;
  Texture2D f_Sprite;
  Color f_HoverTint;
  Color f_TextColor;
  std::string f_Text;
  Font f_Font;
  int f_FontSize;
  bool f_IsHover;
};



void RenderButtons(Button Buttons[], int Amount);

void Input(Button Buttons[], int& Hovering, int Amount);

};

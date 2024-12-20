﻿#pragma once

#include <string>

#include "raylib.h"

#include "Layout.h"

namespace UI {

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
  bool f_IsTextCenter;
};

void CreateButton(Button& f_Button, std::string Text, Margin k_Margin, Padding k_Padding, int k_Fontsize, int Index);

void RenderButtons(Button Buttons[], int Amount);

void InputButton(Button Buttons[], int& Hovering, int Amount);

} // namespace UI

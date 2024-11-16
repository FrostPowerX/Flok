#pragma once

#include "raylib.h"

namespace Parallax {

void InitParallax();

void UnloadParallax();

void UpdateParallax(const float Speed);

void DrawBackground();

void DrawMidground();

void DrawMidground2();

void DrawFrontground();

} // namespace Parallax

#pragma once

#include "Structures.h"


void CalcVertexRectangle(RectangleObject* rectangle);

void ConvertCoordinateWorldToScreenRectangle(RectangleObject* rectangle);

void ConvertUnitPixelToMapRectangle(RectangleObject* rectangle);

void ScreenPrintfRectangle(const int x, const int y, const RectangleObject* rectangle);
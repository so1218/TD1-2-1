#include "Structures.h"


void CalcVertexRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->vertex.leftTop.x = rectangle->pos.x - rectangle->width / 2.0f;
    rectangle->vertex.leftTop.y = rectangle->pos.y + rectangle->height / 2.0f;
    rectangle->vertex.rightTop.x = rectangle->pos.x + rectangle->width / 2.0f;
    rectangle->vertex.rightTop.y = rectangle->pos.y + rectangle->height / 2.0f;
    rectangle->vertex.lehtBottom.x = rectangle->pos.x - rectangle->width / 2.0f;
    rectangle->vertex.lehtBottom.y = rectangle->pos.y - rectangle->height / 2.0f;
    rectangle->vertex.rightBottom.x = rectangle->pos.x + rectangle->width / 2.0f;
    rectangle->vertex.rightBottom.y = rectangle->pos.y - rectangle->height / 2.0f;
}

void ConvertWorldToScreenRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->screenVertex = rectangle->vertex;
    rectangle->screenVertex.leftTop.y -= kWindowHeight;
    rectangle->screenVertex.leftTop.y *= -1.0f;
    rectangle->screenVertex.rightTop.y -= kWindowHeight;
    rectangle->screenVertex.rightTop.y *= -1.0f;
    rectangle->screenVertex.lehtBottom.y -= kWindowHeight;
    rectangle->screenVertex.lehtBottom.y *= -1.0f;
    rectangle->screenVertex.rightBottom.y -= kWindowHeight;
    rectangle->screenVertex.rightBottom.y *= -1.0f;
}

void ConvertUnitPixelToMapRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->mapVertex.leftTop.x = static_cast<int>(rectangle->screenVertex.leftTop.x / 50.0f);
    rectangle->mapVertex.leftTop.y = static_cast<int>(rectangle->screenVertex.leftTop.y / 50.0f);
    rectangle->mapVertex.rightTop.x = static_cast<int>(rectangle->screenVertex.rightTop.x / 50.0f);
    rectangle->mapVertex.rightTop.y = static_cast<int>(rectangle->screenVertex.rightTop.y / 50.0f);
    rectangle->mapVertex.leftBottom.x = static_cast<int>(rectangle->screenVertex.lehtBottom.x / 50.0f);
    rectangle->mapVertex.leftBottom.y = static_cast<int>(rectangle->screenVertex.lehtBottom.y / 50.0f);
    rectangle->mapVertex.rightBottom.x = static_cast<int>(rectangle->screenVertex.rightBottom.x / 50.0f);
    rectangle->mapVertex.rightBottom.y = static_cast<int>(rectangle->screenVertex.rightBottom.y / 50.0f);
}

void ScreenPrintfRectangle(const int x, const int y, const RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    Novice::ScreenPrintf(x, y, "mapVertex.TL { %d, ", rectangle->mapVertex.leftTop.y);
    Novice::ScreenPrintf(x + 140, y, "%d }", rectangle->mapVertex.leftTop.x);
    Novice::ScreenPrintf(x, y + 20, "mapVertex.TR { %d, ", rectangle->mapVertex.rightTop.y);
    Novice::ScreenPrintf(x + 140, y + 20, "%d }", rectangle->mapVertex.rightTop.x);
    Novice::ScreenPrintf(x, y + 40, "mapVertex.BL { %d, ", rectangle->mapVertex.leftBottom.y);
    Novice::ScreenPrintf(x + 140, y + 40, "%d }", rectangle->mapVertex.leftBottom.x);
    Novice::ScreenPrintf(x, y + 60, "mapVertex.BR { %d, ", rectangle->mapVertex.rightBottom.y);
    Novice::ScreenPrintf(x + 140, y + 60, "%d }", rectangle->mapVertex.rightBottom.x);
}
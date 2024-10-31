#include "Structures.h"


void CalcVertexRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->vertex.TL.x = rectangle->pos.x - rectangle->radius.x;
    rectangle->vertex.TL.y = rectangle->pos.y + rectangle->radius.y;
    rectangle->vertex.TR.x = rectangle->pos.x + rectangle->radius.x;
    rectangle->vertex.TR.y = rectangle->pos.y + rectangle->radius.y;
    rectangle->vertex.BL.x = rectangle->pos.x - rectangle->radius.x;
    rectangle->vertex.BL.y = rectangle->pos.y - rectangle->radius.y;
    rectangle->vertex.BR.x = rectangle->pos.x + rectangle->radius.x;
    rectangle->vertex.BR.y = rectangle->pos.y - rectangle->radius.y;
}

void ConvertCoordinateWorldToScreenRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->sVertex = rectangle->vertex;
    rectangle->sVertex.TL.y -= 700.0f;
    rectangle->sVertex.TL.y *= -1.0f;
    rectangle->sVertex.TR.y -= 700.0f;
    rectangle->sVertex.TR.y *= -1.0f;
    rectangle->sVertex.BL.y -= 700.0f;
    rectangle->sVertex.BL.y *= -1.0f;
    rectangle->sVertex.BR.y -= 700.0f;
    rectangle->sVertex.BR.y *= -1.0f;
}

void ConvertUnitPixelToMapRectangle(RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    rectangle->mVertex.TL.x = static_cast<int>(rectangle->sVertex.TL.x / 50.0f);
    rectangle->mVertex.TL.y = static_cast<int>(rectangle->sVertex.TL.y / 50.0f);
    rectangle->mVertex.TR.x = static_cast<int>(rectangle->sVertex.TR.x / 50.0f);
    rectangle->mVertex.TR.y = static_cast<int>(rectangle->sVertex.TR.y / 50.0f);
    rectangle->mVertex.BL.x = static_cast<int>(rectangle->sVertex.BL.x / 50.0f);
    rectangle->mVertex.BL.y = static_cast<int>(rectangle->sVertex.BL.y / 50.0f);
    rectangle->mVertex.BR.x = static_cast<int>(rectangle->sVertex.BR.x / 50.0f);
    rectangle->mVertex.BR.y = static_cast<int>(rectangle->sVertex.BR.y / 50.0f);
}

void ScreenPrintfRectangle(const int x, const int y, const RectangleObject* rectangle) {
    if (rectangle == nullptr) return; // nullptr チェック

    Novice::ScreenPrintf(x, y, "mVertex.TL { %d, ", rectangle->mVertex.TL.y);
    Novice::ScreenPrintf(x + 140, y, "%d }", rectangle->mVertex.TL.x);
    Novice::ScreenPrintf(x, y + 20, "mVertex.TR { %d, ", rectangle->mVertex.TR.y);
    Novice::ScreenPrintf(x + 140, y + 20, "%d }", rectangle->mVertex.TR.x);
    Novice::ScreenPrintf(x, y + 40, "mVertex.BL { %d, ", rectangle->mVertex.BL.y);
    Novice::ScreenPrintf(x + 140, y + 40, "%d }", rectangle->mVertex.BL.x);
    Novice::ScreenPrintf(x, y + 60, "mVertex.BR { %d, ", rectangle->mVertex.BR.y);
    Novice::ScreenPrintf(x + 140, y + 60, "%d }", rectangle->mVertex.BR.x);
}
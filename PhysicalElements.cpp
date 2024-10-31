#include "Structures.h"

void Gravity(float* positionY, PhysicalElements* elements) {
    if (elements == nullptr || positionY == nullptr) return; // nullptr チェック

    elements->velocity.y -= elements->acceleration.y;
    *positionY -= elements->velocity.y;
}

void Gravity(Vector2* position, PhysicalElements* elements) {
    if (elements == nullptr || position == nullptr) return; // nullptr チェック

    elements->velocity.x -= elements->acceleration.x;
    position->x -= elements->velocity.x;
    elements->velocity.y -= elements->acceleration.y;
    position->y -= elements->velocity.y;
}



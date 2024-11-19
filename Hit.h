#pragma once

#include "Structures.h"

bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2);

void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos);

//無敵時間があるノックバック関数
void ApplyKnockbackPlayer(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos, Player* player);
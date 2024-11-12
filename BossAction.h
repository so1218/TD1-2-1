#pragma once

#include "Structures.h"

// ボスの行動パターン

//弾をいくつかの方向に発射する関数
void FireSomewayDirectionBullet(Bullet* bullet, Vector2 startPos);
void DrawSomewayDirectionBullet(Bullet* bullet);
void InitSomewayDirectionBullet(Bullet* bullet);

//弾をプレイヤーに向かって撃つ関数
void FireToSomethingBullet(Bullet* bullet, Vector2* start, Vector2* end);
void DrawToSomethingBullet(Bullet* bullet);
void InitToSomethingBullet(Bullet* bullet);
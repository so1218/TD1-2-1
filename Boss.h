#pragma once

#include "Structures.h"

// ボスの更新処理
void UpdateMoveBoss(Boss* boss, Player* player);

void UpdateMoveBossT1(Boss* boss, Player* player);

// ボスの描画処理
void DrawBoss(Boss* boss);

//ボスの初期化
void InitBoss(Boss* boss, Map* map);
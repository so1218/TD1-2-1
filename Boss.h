#pragma once

#include "Structures.h"

// ボスの更新処理
void UpdateMoveBoss(BossType1* bossT1, Player* player);

void UpdateMoveBossT1(BossType1* bossT1, Player* player);

// ボスの描画処理
void DrawBoss(BossType1* bossT1);

//ボスの初期化
void InitBoss(BossType1* bossT1, Map* map);
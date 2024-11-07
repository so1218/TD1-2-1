#pragma once

#include "Structures.h"

// セレクトシーンの更新処理
Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player, BossType1* bossT1, PlayScene* ps);

// セレクトシーンの描画処理
void DrawSelectScene(SelectScene* ss);

// セレクトシーンの初期化
void InitSelectScene(SelectScene* ss);

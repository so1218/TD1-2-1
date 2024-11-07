#pragma once

#include "Novice.h"
#include "Structures.h"

// プレイシーンの更新処理
Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm, BossType1* bossT1, SelectScene* ss);

// プレイシーンの描画処理
void DrawPlayScene(PlayScene* ps, Map* map, Player* player, BossType1* bossT1);

// プレイシーンの初期化処理
void InitPlayScene(PlayScene* ps);

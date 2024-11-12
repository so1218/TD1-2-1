#pragma once

#include "Novice.h"
#include "Structures.h"

// プレイシーンの更新処理
Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm, Boss* boss, SelectScene* ss, Map* map);

// プレイシーンの描画処理
void DrawPlayScene(PlayScene* ps, Map* map, Player* player, Boss* boss);

// プレイシーンの初期化処理
void InitPlayScene(PlayScene* ps, Boss* boss, Player* player, Map* map);

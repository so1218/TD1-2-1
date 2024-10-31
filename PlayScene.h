#pragma once

#include "Novice.h"
#include "Structures.h"

// プレイシーンの更新処理
Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm);

// プレイシーンの描画処理
void DrawPlayScene(Map* map, Player* player);

// プレイシーンの初期化処理
void InitPlayScene();

#pragma once

#include "Structures.h"

// プレイヤーの移動処理
void MovePlayer(Player* player, GameManager* gm);

// プレイヤーの描画処理
void DrawPlayer(Player* player);

// プレイヤーのデバッグ表示
void ScreenPrintfPlayScene();

// プレイヤーの初期化
void InitPlayer(Player* player, Map* map);

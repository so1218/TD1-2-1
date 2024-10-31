#pragma once

#include "Structures.h"

// セレクトシーンの更新処理
Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player);

// セレクトシーンの描画処理
void DrawSelectScene();

// セレクトシーンの初期化
void InitSelectScene();

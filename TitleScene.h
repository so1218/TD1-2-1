#pragma once

#include "Structures.h"

// タイトルシーンの更新処理
Scene UpdateTitleScene(TitleScene* ts, SelectScene* ss);

// タイトルシーンの描画処理
void DrawTitleScene(TitleScene* ts);

// タイトルシーンの初期化
void InitTitleScene(TitleScene* ts);

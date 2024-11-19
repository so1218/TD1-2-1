#pragma once

#include "Structures.h"

// マウス座標をワールド座標に変換する関数（例）
IntVector2 ConvertScreenToWorld(const IntVector2& screenPos);

//==============================
//自機の弾発射に関わる関数
//==============================

// 電極の初期化
void InitElectrode(Electrode* electrode, Player* player);

// 電極の更新処理
void MoveElectrode(Electrode* electrode, Player* player, GameManager* gm);

// 電極の描画処理
void DrawElectrode(Electrode* electrode);

//==============================
// 自機のマーカー設置に関わる関数
//==============================

void InitMaker(Player* player);

void MoveMaker(Player* player);

void DrawMaker(Player* player);

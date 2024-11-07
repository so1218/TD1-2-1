#include "Structures.h"
#include "Rectangle.h"
#include "Easing.h"
#include "Calculate.h"
#include "Boss.h"
#include "Particle.h"


//========================================================
// ボスの更新処理
//========================================================

void UpdateMoveBoss(BossType1* bossT1, Player* player)
{

	UpdateMoveBossT1(bossT1, player);

}

void UpdateMoveBossT1(BossType1* bossT1, Player* player)
{
	CalcVertexRectangle(bossT1);
	ConvertWorldToScreenRectangle(bossT1);

	bossT1->toPlayerDistance = CalculateDistance(bossT1->pos, player->pos);

	// 距離に基づいてインターバル変更
	if (bossT1->toPlayerDistance < 200.0f)
	{
		bossT1->MoveEase.interval = 0.000002f;
	}
	else if (bossT1->toPlayerDistance < 400.0f)
	{
		bossT1->MoveEase.interval = 0.000008f;
	}
	else
	{
		bossT1->MoveEase.interval = 0.00001f;
	}

	UpdateCenterToAroundParticle(bossT1->aroundParticle, &bossT1->pos);

	LinearInterpolation(bossT1->pos, player->pos, bossT1->pos, bossT1->MoveEase);
	CountEaseTimerMoveBossT1(bossT1->MoveEase);
}



//========================================================
// ボスの描画処理
//========================================================

void DrawBoss(BossType1* bossT1)
{
	Novice::DrawQuad(
		static_cast<int>(bossT1->screenVertex.leftTop.x),
		static_cast<int>(bossT1->screenVertex.leftTop.y),
		static_cast<int>(bossT1->screenVertex.rightTop.x),
		static_cast<int>(bossT1->screenVertex.rightTop.y),
		static_cast<int>(bossT1->screenVertex.lehtBottom.x),
		static_cast<int>(bossT1->screenVertex.lehtBottom.y),
		static_cast<int>(bossT1->screenVertex.rightBottom.x),
		static_cast<int>(bossT1->screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, bossT1->color);

	DrawCenterToAroundParticle(bossT1->aroundParticle);
}

//========================================================
// ボスの初期化
//========================================================

void InitBoss(BossType1* bossT1, Map* map)
{
	//ボス1の初期位置初期化
	bossT1->startChipNo = { 6, 8 };

	bossT1->radius = { 25.0f, 25.0f };
	bossT1->velocity = { 5.0f, 5.0f };

	bossT1->width = 50;
	bossT1->height = 50;
	bossT1->color = RED;

	bossT1->aroundParticle->amount = 16;

	bossT1->MoveEase.interval = 0.000005f;

	//開始位置座標

	//初期位置チップナンバー
	if (map->stageNo == 0)
	{
		bossT1->startChipNo.x = 3;
		bossT1->startChipNo.y = 3;
	}

	else if (map->stageNo == 1)
	{
		bossT1->startChipNo.x = 9;
		bossT1->startChipNo.y = 8;
	}

	else if (map->stageNo == 2)
	{
		bossT1->startChipNo.x = 10;
		bossT1->startChipNo.y = 6;
	}

	else if (map->stageNo == 3)
	{
		bossT1->startChipNo.x = 10;
		bossT1->startChipNo.y = 8;
	}

	else if (map->stageNo == 4)
	{
		bossT1->startChipNo.x = 7;
		bossT1->startChipNo.y = 9;
	}

	else if (map->stageNo == 5)
	{
		bossT1->startChipNo.x = 10;
		bossT1->startChipNo.y = 6;
	}

	else if (map->stageNo == 6)
	{
		bossT1->startChipNo.x = 9;
		bossT1->startChipNo.y = 8;
	}

	else if (map->stageNo == 7)
	{
		bossT1->startChipNo.x = 10;
		bossT1->startChipNo.y = 5;
	}

	else if (map->stageNo == 8)
	{
		bossT1->startChipNo.x = 9;
		bossT1->startChipNo.y = 9;
	}

	else if (map->stageNo == 9)
	{
		bossT1->startChipNo.x = 13;
		bossT1->startChipNo.y = 4;
	}

	bossT1->pos = map->chip[bossT1->startChipNo.y][bossT1->startChipNo.x].pos;

	bossT1->currentChipNo = bossT1->startChipNo;
	bossT1->prePos = bossT1->pos;

	CalcVertexRectangle(bossT1);
	ConvertWorldToScreenRectangle(bossT1);

}
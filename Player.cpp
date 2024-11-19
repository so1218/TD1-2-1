#include "Structures.h"
#include "Rectangle.h"
#include "Particle.h"
#include "electrode.h"

//========================================================
// プレイヤーの挙動
//========================================================

void MovePlayer(Player* player, GameManager* gm)
{

	//パッドでの移動
	
	if (gm->numJoysticks > 0)
	{
		int x, y;

		if (Novice::GetAnalogInputLeft(0, &x, &y))
		{
			if (x > 0x4000)
			{
				player->pos.x += player->velocity.x;
			}
			if (x < -0x4000)
			{
				player->pos.x -= player->velocity.x;
			}

			if (y > 0x4000)
			{
				player->pos.y -= player->velocity.y;
			}
			if (y < -0x4000)
			{
				player->pos.y += player->velocity.y;
			}
		}
	}

	//キーボードでの移動
	if (gm->keys[DIK_D])
	{
		player->pos.x += player->velocity.x;
	}
	if (gm->keys[DIK_A])
	{
		player->pos.x -= player->velocity.x;
	}
	if (gm->keys[DIK_W])
	{
		player->pos.y += player->velocity.y;
	}
	if (gm->keys[DIK_S])
	{
		player->pos.y -= player->velocity.y;
	}

	MoveElectrode(player->electrode,player,gm);

	MoveMaker(player);

	CalcVertexRectangle(player);
	ConvertWorldToScreenRectangle(player);

	UpdateGoUpAroundParticle(player->aroundParticle, &player->pos);
}


//========================================================
// プレイヤーの描画処理
//========================================================

// プレイヤーのデバック(デバックモードのみ)
void ScreenPrintfPlayer()
{
	Novice::ScreenPrintf(0, 20, "player");
	
	
}

//	プレイヤーの描画
void DrawPlayer(Player* player)
{
	Novice::DrawQuad(
		static_cast<int>(player->screenVertex.leftTop.x),
		static_cast<int>(player->screenVertex.leftTop.y),
		static_cast<int>(player->screenVertex.rightTop.x),
		static_cast<int>(player->screenVertex.rightTop.y),
		static_cast<int>(player->screenVertex.lehtBottom.x),
		static_cast<int>(player->screenVertex.lehtBottom.y),
		static_cast<int>(player->screenVertex.rightBottom.x),
		static_cast<int>(player->screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, player->color);

	DrawGoUpAroundParticle(player->aroundParticle);

	DrawElectrode(player->electrode);

	DrawMaker(player);


#if defined(_DEBUG)
	ScreenPrintfPlayer();
#endif
}

//========================================================
// プレイヤーの初期化
//========================================================

void InitPlayer(Player* player, Map* map)
{
	//プレイヤーの初期位置初期化
	player->startChipNo = { 6, 8 };

	player->radius = { 16.0f, 16.0f };
	player->velocity = { 5.0f, 5.0f };

	player->width = 32;
	player->height = 32;
	player->color = BLUE;

	player->aroundParticle->amount = 16;
	player->aroundParticle->emitterRange = { 20,60 };
	
	//開始位置座標

	//初期位置チップナンバー
	if (map->stageNo == 0)
	{
		player->startChipNo.x = 10;
		player->startChipNo.y = 8;
	}

	else if (map->stageNo == 1)
	{
		player->startChipNo.x = 9;
		player->startChipNo.y = 8;
	}

	else if (map->stageNo == 2)
	{
		player->startChipNo.x = 10;
		player->startChipNo.y = 6;
	}

	else if (map->stageNo == 3)
	{
		player->startChipNo.x = 10;
		player->startChipNo.y = 8;
	}

	else if (map->stageNo == 4)
	{
		player->startChipNo.x = 7;
		player->startChipNo.y = 9;
	}

	else if (map->stageNo == 5)
	{
		player->startChipNo.x = 10;
		player->startChipNo.y = 6;
	}

	else if (map->stageNo == 6)
	{
		player->startChipNo.x = 9;
		player->startChipNo.y = 8;
	}

	else if (map->stageNo == 7)
	{
		player->startChipNo.x = 10;
		player->startChipNo.y = 5;
	}

	else if (map->stageNo == 8)
	{
		player->startChipNo.x = 9;
		player->startChipNo.y = 9;
	}

	else if (map->stageNo == 9)
	{
		player->startChipNo.x = 13;
		player->startChipNo.y = 4;
	}

	player->pos = map->chip[player->startChipNo.y][player->startChipNo.x].pos;

	player->currentChipNo = player->startChipNo;
	player->prePos = player->pos;

	InitElectrode(player->electrode, player);

	InitMaker(player);

	CalcVertexRectangle(player);
	ConvertWorldToScreenRectangle(player);
}

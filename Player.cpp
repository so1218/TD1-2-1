#include "Structures.h"
#include "Rectangle.h"
#include "Particle.h"
#include "Hit.h"
#include <deque>
#include "GrovalTextureHandles.h"

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

	//残像の処理
	player->afterImage.frameCounter++;

	if (player->afterImage.frameCounter >= 3)
	{
	
		player->afterImage.posHistory.push_front(player->pos);

		
		if (player->afterImage.posHistory.size() > player->afterImage.maxHistory)
		{
			player->afterImage.posHistory.pop_back();
		}

		// フレームカウンタをリセット
		player->afterImage.frameCounter = 0;
	}

	CalcVertexRectangle(player);
	ConvertWorldToScreenRectangle(player);
	
	UpdateToCenterParticle(player->toCenterParticle, &player->pos);
	UpdateLikeSmokeParticle(player->likeSmokeParticle, &player->pos);
}


//========================================================
// プレイヤーの描画処理
//========================================================

// プレイヤーのデバック(デバックモードのみ)
void ScreenPrintfPlayer(Player* player)
{
	Novice::ScreenPrintf(0, 20, "player");
	Novice::ScreenPrintf(0, 40, "HP : %d",player->HP);
	Novice::ScreenPrintf(0, 60, "isKnockback : %d", player->knockback.isKnockbacked);
	
}

//	プレイヤーの描画
void DrawPlayer(Player* player)
{

	// 残像を描画
	for (int i = 0; i < player->afterImage.posHistory.size(); ++i)
	{
		
		player->afterImage.pastPos = player->afterImage.posHistory[i];

		
		player->afterImage.colorAlpha = 1.0f - (i / static_cast<float>(player->afterImage.maxHistory));

		Novice::DrawQuad(
			static_cast<int>(player->afterImage.pastPos.x - player->width / 2), kWindowHeight - static_cast<int>(player->afterImage.pastPos.y - player->height / 2), 
			static_cast<int>(player->afterImage.pastPos.x + player->width / 2), kWindowHeight - static_cast<int>(player->afterImage.pastPos.y - player->height / 2), 
			static_cast<int>(player->afterImage.pastPos.x - player->width / 2), kWindowHeight - static_cast<int>(player->afterImage.pastPos.y + player->height / 2), 
			static_cast<int>(player->afterImage.pastPos.x + player->width / 2), kWindowHeight - static_cast<int>(player->afterImage.pastPos.y + player->height / 2), 
			0, 0, 0, 0, 0, (player->afterImage.colorRGB << 8) | static_cast<unsigned int>(player->afterImage.colorAlpha * 255));
	}


	Novice::DrawQuad(
		static_cast<int>(player->screenVertex.leftTop.x),
		static_cast<int>(player->screenVertex.leftTop.y),
		static_cast<int>(player->screenVertex.rightTop.x),
		static_cast<int>(player->screenVertex.rightTop.y),
		static_cast<int>(player->screenVertex.leftBottom.x),
		static_cast<int>(player->screenVertex.leftBottom.y),
		static_cast<int>(player->screenVertex.rightBottom.x),
		static_cast<int>(player->screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, player->color);

	DrawLikeSmokeParticle(player->likeSmokeParticle);
	DrawToCenterParticle(player->toCenterParticle);

#if defined(_DEBUG)
	ScreenPrintfPlayer(player);
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

	//パーティクルに関する初期化
	player->likeSmokeParticle->amount = 30;
	player->likeSmokeParticle->emitterRange = { 20,60 };
	player->toCenterParticle->amount = 12;
	InitToCenterParticle(player->toCenterParticle);
	

	//四角形描画に関する初期化
	CalcVertexRectangle(player);
	ConvertWorldToScreenRectangle(player);
	
	//残像に関する初期化
	player->afterImage.colorRGB = 0x00edff;
	
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

	

	player->pos = map->chip[player->startChipNo.y][player->startChipNo.x].pos;

	player->currentChipNo = player->startChipNo;
	player->prePos = player->pos;

}

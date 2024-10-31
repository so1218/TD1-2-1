#include "Structures.h"

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
		static_cast<int>(player->pos.x - player->width / 2),
		kWindowHeight - static_cast<int>(player->pos.y - player->height / 2),
		static_cast<int>(player->pos.x + player->width / 2),
		kWindowHeight - static_cast<int>(player->pos.y - player->height / 2),
		static_cast<int>(player->pos.x - player->width / 2),
		kWindowHeight - static_cast<int>(player->pos.y + player->height / 2),
		static_cast<int>(player->pos.x + player->width / 2),
		kWindowHeight - static_cast<int>(player->pos.y + player->height / 2),
		0, 0, 0, 0, 0, player->color);


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
	static IntVector2 start = { 6, 8 };

	player->radius = { 25.0f, 25.0f };
	player->velocity = { 5.0f, 5.0f };

	player->width = 50;
	player->height = 50;
	player->color = BLUE;

	//開始位置座標

	//初期位置チップナンバー
	if (map->stageNo == 0)
	{
		start.x = 10;
		start.y = 8;
	}

	else if (map->stageNo == 1)
	{
		start.x = 9;
		start.y = 8;
	}

	else if (map->stageNo == 2)
	{
		start.x = 10;
		start.y = 6;
	}

	else if (map->stageNo == 3)
	{
		start.x = 10;
		start.y = 8;
	}

	else if (map->stageNo == 4)
	{
		start.x = 7;
		start.y = 9;
	}

	else if (map->stageNo == 5)
	{
		start.x = 10;
		start.y = 6;
	}

	else if (map->stageNo == 6)
	{
		start.x = 9;
		start.y = 8;
	}

	else if (map->stageNo == 7)
	{
		start.x = 10;
		start.y = 5;
	}

	else if (map->stageNo == 8)
	{
		start.x = 9;
		start.y = 9;
	}

	else if (map->stageNo == 9)
	{
		start.x = 13;
		start.y = 4;
	}

	player->pos = map->chip[start.y][start.x].pos;

	player->currentChipNo = start;
	player->prePos = player->pos;

}

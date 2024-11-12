#include "Structures.h"
#include "Map.h"
#include "Rectangle.h"
#include "Player.h"
#include "Boss.h"
#include "Particle.h"
#include "Easing.h"
#include "PlayScene.h"

//========================================================
// セレクトシーンの更新処理
//========================================================

Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player, Boss* boss, PlayScene* ps, GameManager* gm)
{
	Scene nextScene = Select;

	if (ss->fadeIn.isEase)
	{
		ColorLinearInterpolation(ss->fadeColor, transparent, ss->fadeColor, ss->fadeIn);
		CountEaseInOutTimer(ss->fadeIn);
	}

	else
	{
		MovePlayer(player, gm);

		// チュートリアルステージに入る処理
		if (ss->tutorialPos.x <= player->pos.x && ss->tutorialPos.x + ss->tutorialWidth >= player->pos.x + player->radius.x)
		{
			if (ss->tutorialPos.y >= player->pos.y && ss->tutorialPos.y + ss->tutorialHeight <= player->pos.y + player->radius.y)
			{
				
				ss->fadeOut.isEase = true;
				ss->isNextScene = true;
			}
		}

		// ステージ1に入る処理
		if (ss->stageOnePos.x <= player->pos.x && ss->stageOnePos.x + ss->stageOneWidth >= player->pos.x + player->radius.x)
		{
			if (ss->stageOnePos.y >= player->pos.y && ss->stageOnePos.y + ss->stageOneHeight <= player->pos.y + player->radius.y)
			{
				
				ss->fadeOut.isEase = true;
				ss->isNextScene = true;
			}
		}

		// ステージ2に入る処理
		if (ss->stageTwoPos.x <= player->pos.x && ss->stageTwoPos.x + ss->stageTwoWidth >= player->pos.x + player->radius.x)
		{
			if (ss->stageTwoPos.y >= player->pos.y && ss->stageTwoPos.y + ss->stageTwoHeight <= player->pos.y + player->radius.y)
			{
				
				ss->fadeOut.isEase = true;
				ss->isNextScene = true;
			}
		}

		// ステージ3に入る処理
		if (ss->stageThreePos.x <= player->pos.x && ss->stageThreePos.x + ss->stageThreeWidth >= player->pos.x + player->radius.x)
		{
			if (ss->stageThreePos.y >= player->pos.y && ss->stageThreePos.y + ss->stageThreeHeight <= player->pos.y + player->radius.y)
			{
				
				ss->fadeOut.isEase = true;
				ss->isNextScene = true;
			}
		}

		//次のシーンへのトリガー
		if (ss->gm->keys[DIK_SPACE] && !ss->gm->preKeys[DIK_SPACE])
		{
			ss->fadeOut.isEase = true;
			ss->isNextScene = true;
			
		}

		if (ss->isNextScene)
		{
			if (ss->fadeOut.isEase)
			{
				ColorLinearInterpolation(ss->fadeColor, opaque, ss->fadeColor, ss->fadeOut);
				CountEaseInOutTimer(ss->fadeOut);
			}
			else
			{
				MapSetting(map);
				InitPlayScene(ps, boss, player, map);
				
				nextScene = Play;

			}
		}
	}

	return nextScene;

}

//========================================================
// セレクトシーンの描画処理
//========================================================

// セレクトシーンのデバック(デバックモードのみ)
void ScreenPrintfSelectScene()
{
	Novice::ScreenPrintf(0, 0, "Select");
}

// セレクトシーンの描画
void DrawSelectScene(SelectScene* ss, Player* player)
{

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ss->fadeColor, kFillModeSolid);

	SelectScene selectscene;

	// チュートリアルステージの描画処理
	Novice::DrawBox(static_cast<int>(selectscene.tutorialPos.x), static_cast<int>(selectscene.tutorialPos.y), 
		static_cast<int>(selectscene.tutorialWidth), static_cast<int>(selectscene.tutorialHeight),0.0f,BLACK,kFillModeSolid);

	// ステージ1の描画処理
	Novice::DrawBox(static_cast<int>(selectscene.stageOnePos.x), static_cast<int>(selectscene.stageOnePos.y),
		static_cast<int>(selectscene.stageOneWidth), static_cast<int>(selectscene.stageOneHeight), 0.0f, WHITE, kFillModeSolid);

	// ステージ2の描画処理
	Novice::DrawBox(static_cast<int>(selectscene.stageTwoPos.x), static_cast<int>(selectscene.stageTwoPos.y),
		static_cast<int>(selectscene.stageTwoWidth), static_cast<int>(selectscene.stageTwoHeight), 0.0f, RED, kFillModeSolid);


	// ステージ3の描画処理
	Novice::DrawBox(static_cast<int>(selectscene.stageThreePos.x), static_cast<int>(selectscene.stageThreePos.y),
		static_cast<int>(selectscene.stageThreeWidth), static_cast<int>(selectscene.stageThreeHeight), 0.0f, BLUE, kFillModeSolid);

	DrawPlayer(player);

#if defined(_DEBUG)
	ScreenPrintfSelectScene();
#endif
}

//========================================================
// セレクトシーンの初期化
//========================================================

void InitSelectScene(SelectScene* ss, Player* player, Map* map)
{
	ss->fadeIn.isEase = true;
	ss->isNextScene = false;

	InitPlayer(player, map);
}
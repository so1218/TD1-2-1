#include "Structures.h"
#include "Map.h"
#include "Player.h"

//========================================================
// セレクトシーンの更新処理
//========================================================

Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player)
{
	Scene nextScene = Select;
	SelectScene selectscene;
	
	// チュートリアルステージに入る処理
	if (selectscene.tutorialPos.x <= player->pos.x && selectscene.tutorialPos.x + selectscene.tutorialWidth >= player->pos.x + player->radius.x)
	{
		if (selectscene.tutorialPos.y >= player->pos.y && selectscene.tutorialPos.y + selectscene.tutorialHeight <= player->pos.y + player->radius.y)
		{
			nextScene = Play;
		}
	}

	// ステージ1に入る処理
	if (selectscene.stageOnePos.x <= player->pos.x && selectscene.stageOnePos.x + selectscene.stageOneWidth >= player->pos.x + player->radius.x)
	{
		if (selectscene.stageOnePos.y >= player->pos.y && selectscene.stageOnePos.y + selectscene.stageOneHeight <= player->pos.y + player->radius.y)
		{
			nextScene = Play;
		}
	}

	// ステージ2に入る処理
	if (selectscene.stageTwoPos.x <= player->pos.x && selectscene.stageTwoPos.x + selectscene.stageTwoWidth >= player->pos.x + player->radius.x)
	{
		if (selectscene.stageTwoPos.y >= player->pos.y && selectscene.stageTwoPos.y + selectscene.stageTwoHeight <= player->pos.y + player->radius.y)
		{
			nextScene = Play;
		}
	}

	// ステージ3に入る処理
	if (selectscene.stageThreePos.x <= player->pos.x && selectscene.stageThreePos.x + selectscene.stageThreeWidth >= player->pos.x + player->radius.x)
	{
		if (selectscene.stageThreePos.y >= player->pos.y && selectscene.stageThreePos.y + selectscene.stageThreeHeight <= player->pos.y + player->radius.y)
		{
			nextScene = Play;
		}
	}

	if (ss->gm->keys[DIK_SPACE] && !ss->gm->preKeys[DIK_SPACE])
	{
		MapSetting(map);
		InitPlayer(player, map);
		Novice::SetJoystickDeadZone(0, 8000, 8000); // 左右スティックのデッドゾーンを設定
		nextScene = Play;
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
void DrawSelectScene()
{
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

#if defined(_DEBUG)
	ScreenPrintfSelectScene();
#endif
}

//========================================================
// セレクトシーンの初期化
//========================================================

void InitSelectScene() 
{

}
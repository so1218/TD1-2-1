#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Boss.h"

//========================================================
// プレイシーンの更新処理
//========================================================

Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm, BossType1* bossT1, SelectScene* ss)
{
	Scene nextScene = Play;

	if (ps->fadeIn.isEase)
	{
		ColorLinearInterpolation(ps->fadeColor, transparent, ps->fadeColor, ps->fadeIn);
		CountEaseInOutTimer(ps->fadeIn);
	}
	else
	{
		MovePlayer(player, gm);
		UpdateMoveBoss(bossT1, player);

		//次のシーンへのトリガー
		if (ps->gm->keys[DIK_SPACE] && !ps->gm->preKeys[DIK_SPACE])
		{
			ps->fadeOut.isEase = true;
			ps->isNextScene = true;
		}
		if (ps->isNextScene)
		{
			if (ps->fadeOut.isEase)
			{
				ColorLinearInterpolation(ps->fadeColor, opaque, ps->fadeColor, ps->fadeOut);
				CountEaseInOutTimer(ps->fadeOut);
			}
			else
			{
				InitSelectScene(ss);
				nextScene = Select;
			}
		}

	}
	

	
				
	return nextScene;

}

//========================================================
// プレイシーンの描画処理
//========================================================

// プレイシーンのデバック(デバックモードのみ)
void ScreenPrintfPlayScene()
{
	Novice::ScreenPrintf(0, 0, "Play");
}

// プレイシーンの描画
void DrawPlayScene(PlayScene* ps, Map* map, Player* player, BossType1* bossT1)
{
	DrawMap(map);
	DrawBoss(bossT1);
	DrawPlayer(player);

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ps->fadeColor, kFillModeSolid);
	
#if defined(_DEBUG)
	ScreenPrintfPlayScene();
#endif
}

//========================================================
// プレイシーンの初期化
//========================================================

void InitPlayScene(PlayScene* ps)
{
	ps->fadeIn.isEase = true;
	ps->isNextScene = false;
}


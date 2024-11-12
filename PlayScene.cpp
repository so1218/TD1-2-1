#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Boss.h"
#include "Particle.h"
#include "Rectangle.h"

//========================================================
// プレイシーンの更新処理
//========================================================

Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm, Boss* boss, SelectScene* ss, Map* map)
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
		UpdateMoveBoss(boss, player);

		for (int i = 0; i < 3; ++i)
		{
			ps->playerHpIcon[i].theta += 1.0f / 100.0f * static_cast<float>(M_PI);

			ps->playerHpIcon[i].pos.y = 650 + cosf(ps->playerHpIcon[i].theta) * 10.0f;

			CalcVertexRectangle(&ps->playerHpIcon[i]);
			ConvertWorldToScreenRectangle(&ps->playerHpIcon[i]);
		}

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
				InitSelectScene(ss, player, map);
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
void DrawPlayScene(PlayScene* ps, Map* map, Player* player, Boss* boss)
{
	
	DrawMap(map);
	DrawBoss(boss);
	DrawPlayer(player);

	for (int i = 0; i < 3; ++i)
	{
		Novice::DrawQuad(
			static_cast<int>(ps->playerHpIcon[i].screenVertex.leftTop.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.leftTop.y),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightTop.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightTop.y),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.lehtBottom.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.lehtBottom.y),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightBottom.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ps->playerHpIcon[i].color);
	}


	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ps->fadeColor, kFillModeSolid);
	
#if defined(_DEBUG)
	ScreenPrintfPlayScene();
#endif
}

//========================================================
// プレイシーンの初期化
//========================================================

void InitPlayScene(PlayScene* ps, Boss* boss, Player* player, Map* map)
{
	ps->fadeIn.isEase = true;
	ps->isNextScene = false;

	for (int i = 0; i < 3; ++i)
	{
		ps->playerHpIcon[i].pos.x = static_cast<float>(100 + i * 70);
		ps->playerHpIcon[i].pos.y = 650;

		ps->playerHpIcon[i].width = 50;
		ps->playerHpIcon[i].height = 50;

		CalcVertexRectangle(&ps->playerHpIcon[i]);
		ConvertWorldToScreenRectangle(&ps->playerHpIcon[i]);

	}

	

	InitBoss(boss, map);
	InitPlayer(player, map);

	InitCenterToAroundParticle(boss->T1.aroundParticle);
	InitLikeSmokeParticle(player->aroundParticle);
	Novice::SetJoystickDeadZone(0, 8000, 8000); // 左右スティックのデッドゾーンを設定
}


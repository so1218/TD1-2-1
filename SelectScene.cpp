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

Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player, BossType1* bossT1, PlayScene* ps)
{
	Scene nextScene = Select;
	if (ss->fadeIn.isEase)
	{
		ColorLinearInterpolation(ss->fadeColor, transparent, ss->fadeColor, ss->fadeIn);
		CountEaseInOutTimer(ss->fadeIn);
	}
	else
	{

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
				InitBoss(bossT1, map);
				InitPlayer(player, map);
				InitPlayScene(ps);
				InitCenterToAroundParticle(bossT1->aroundParticle);
				InitGoUpAroundParticle(player->aroundParticle);
				Novice::SetJoystickDeadZone(0, 8000, 8000); // 左右スティックのデッドゾーンを設定

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
void DrawSelectScene(SelectScene* ss)
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ss->fadeColor, kFillModeSolid);


#if defined(_DEBUG)
	ScreenPrintfSelectScene();
#endif
}

//========================================================
// セレクトシーンの初期化
//========================================================

void InitSelectScene(SelectScene* ss)
{
	ss->fadeIn.isEase = true;
	ss->isNextScene = false;
}
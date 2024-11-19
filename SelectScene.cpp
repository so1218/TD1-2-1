#include "Structures.h"
#include "Map.h"
#include "Rectangle.h"
#include "Player.h"
#include "Boss.h"
#include "Particle.h"
#include "Easing.h"
#include "PlayScene.h"
#include"electrode.h"

//========================================================
// セレクトシーンの更新処理
//========================================================

Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player, Boss* boss, PlayScene* ps, GameManager* gm)
{
	Scene nextScene = Select;

	if (ss->fadeIn.isEase)
	{
		ColorLinearInterpolation(ss->fadeIn.startColor, transparent, ss->fadeColor, ss->fadeIn);
		CountEaseInOutTimer(ss->fadeIn);
	}

	else
	{
		if (!ss->isSceneChange)
		{
			MovePlayer(player, gm);

			// チュートリアルステージに入る処理
			if (ss->tutorialDoor.vertex.leftTop.x <= player->pos.x && ss->tutorialDoor.vertex.rightTop.x >= player->pos.x + player->radius.x)
			{
				// 上から侵入できないようにする処理
				if (ss->tutorialDoor.vertex.leftTop.y <= player->pos.y && ss->tutorialDoor.vertex.leftTop.y >= player->pos.y - player->radius.y)
				{
					player->pos.y = ss->tutorialDoor.vertex.leftTop.y + player->radius.y;
				}

				if (ss->tutorialDoor.vertex.leftTop.y >= player->pos.y && ss->tutorialDoor.vertex.leftBottom.y <= player->pos.y - player->radius.y)
				{
					ss->fadeOut.isEase = true;
					ss->isNextScene = true;
					ss->isSceneChange = true;
				}
			}

			if (ss->tutorialDoor.vertex.leftTop.y >= player->pos.y && ss->tutorialDoor.vertex.leftBottom.y <= player->pos.y)
			{
				// 右から侵入できないようにする処理
				if (ss->tutorialDoor.vertex.rightTop.x <= player->pos.x + player->radius.x && ss->tutorialDoor.vertex.rightTop.x >= player->pos.x - player->radius.x)
				{
					player->pos.x = ss->tutorialDoor.vertex.rightTop.x + player->radius.x;
				}

				// 左から侵入できないようにする処理
				if (ss->tutorialDoor.vertex.leftTop.x >= player->pos.x - player->radius.x && ss->tutorialDoor.vertex.leftTop.x <= player->pos.x + player->radius.x)
				{
					player->pos.x = ss->tutorialDoor.vertex.leftTop.x - player->radius.x;
				}
			}

			// ステージ1に入る処理
			if (ss->stageOneDoor.vertex.leftTop.x <= player->pos.x && ss->stageOneDoor.vertex.rightTop.x >= player->pos.x + player->radius.x)
			{
				// 上から侵入できないようにする処理
				if (ss->stageOneDoor.vertex.leftTop.y <= player->pos.y && ss->stageOneDoor.vertex.leftTop.y >= player->pos.y - player->radius.y)
				{
					player->pos.y = ss->stageOneDoor.vertex.leftTop.y + player->radius.y;
				}


				if (ss->stageOneDoor.vertex.leftTop.y >= player->pos.y && ss->stageOneDoor.vertex.leftBottom.y <= player->pos.y - player->radius.y)
				{
					ss->fadeOut.isEase = true;
					ss->isNextScene = true;
					ss->isSceneChange = true;
				}
			}

			if (ss->stageOneDoor.vertex.leftTop.y >= player->pos.y && ss->stageOneDoor.vertex.leftBottom.y <= player->pos.y)
			{
				// 右から侵入できないようにする処理
				if (ss->stageOneDoor.vertex.rightTop.x <= player->pos.x + player->radius.x && ss->stageOneDoor.vertex.rightTop.x >= player->pos.x - player->radius.x)
				{
					player->pos.x = ss->stageOneDoor.vertex.rightTop.x + player->radius.x;
				}

				// 左から侵入できないようにする処理
				if (ss->stageOneDoor.vertex.leftTop.x >= player->pos.x - player->radius.x && ss->stageOneDoor.vertex.leftTop.x <= player->pos.x + player->radius.x)
				{
					player->pos.x = ss->stageOneDoor.vertex.leftTop.x - player->radius.x;
				}
			}

			// ステージ2に入る処理
			if (ss->stageTwoDoor.vertex.leftTop.x <= player->pos.x && ss->stageTwoDoor.vertex.rightTop.x >= player->pos.x + player->radius.x)
			{
				// 上から侵入できないようにする処理
				if (ss->stageTwoDoor.vertex.leftTop.y <= player->pos.y && ss->stageTwoDoor.vertex.leftTop.y >= player->pos.y - player->radius.y)
				{
					player->pos.y = ss->stageTwoDoor.vertex.leftTop.y + player->radius.y;
				}

				if (ss->stageTwoDoor.vertex.leftTop.y >= player->pos.y && ss->stageTwoDoor.vertex.leftBottom.y <= player->pos.y - player->radius.y)
				{
					ss->fadeOut.isEase = true;
					ss->isNextScene = true;
					ss->isSceneChange = true;
				}
			}

			if (ss->stageTwoDoor.vertex.leftTop.y >= player->pos.y && ss->stageTwoDoor.vertex.leftBottom.y <= player->pos.y)
			{
				// 右から侵入できないようにする処理
				if (ss->stageTwoDoor.vertex.rightTop.x <= player->pos.x + player->radius.x && ss->stageTwoDoor.vertex.rightTop.x >= player->pos.x - player->radius.x)
				{
					player->pos.x = ss->stageTwoDoor.vertex.rightTop.x + player->radius.x;
				}

				// 左から侵入できないようにする処理
				if (ss->stageTwoDoor.vertex.leftTop.x >= player->pos.x - player->radius.x && ss->stageTwoDoor.vertex.leftTop.x <= player->pos.x + player->radius.x)
				{
					player->pos.x = ss->stageTwoDoor.vertex.leftTop.x - player->radius.x;
				}
			}


			// ステージ3に入る処理
			if (ss->stageThreeDoor.vertex.leftTop.x <= player->pos.x && ss->stageThreeDoor.vertex.rightTop.x >= player->pos.x + player->radius.x)
			{
				// 上から侵入できないようにする処理
				if (ss->stageThreeDoor.vertex.leftTop.y <= player->pos.y && ss->stageThreeDoor.vertex.leftTop.y >= player->pos.y - player->radius.y)
				{
					player->pos.y = ss->stageThreeDoor.vertex.leftTop.y + player->radius.y;
				}

				if (ss->stageThreeDoor.vertex.leftTop.y >= player->pos.y && ss->stageThreeDoor.vertex.leftBottom.y <= player->pos.y - player->radius.y)
				{
					ss->fadeOut.isEase = true;
					ss->isNextScene = true;
					ss->isSceneChange = true;
				}
			}

			if (ss->stageThreeDoor.vertex.leftTop.y >= player->pos.y && ss->stageThreeDoor.vertex.leftBottom.y <= player->pos.y)
			{
				// 右から侵入できないようにする処理
				if (ss->stageThreeDoor.vertex.rightTop.x <= player->pos.x + player->radius.x && ss->stageThreeDoor.vertex.rightTop.x >= player->pos.x - player->radius.x)
				{
					player->pos.x = ss->stageThreeDoor.vertex.rightTop.x + player->radius.x;
				}

				// 左から侵入できないようにする処理
				if (ss->stageThreeDoor.vertex.leftTop.x >= player->pos.x - player->radius.x && ss->stageThreeDoor.vertex.leftTop.x <= player->pos.x + player->radius.x)
				{
					player->pos.x = ss->stageThreeDoor.vertex.leftTop.x - player->radius.x;
				}
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
				ColorLinearInterpolation(ss->fadeOut.startColor, opaque, ss->fadeColor, ss->fadeOut);
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


				InitPlayScene(ps, boss, player, map);
				
				ss->isSceneChange = false;


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

	SelectScene selectscene;

	// チュートリアルステージの描画処理
	Novice::DrawQuad(static_cast<int>(ss->tutorialDoor.screenVertex.leftTop.x),
		static_cast<int>(ss->tutorialDoor.screenVertex.leftTop.y),
		static_cast<int>(ss->tutorialDoor.screenVertex.rightTop.x),
		static_cast<int>(ss->tutorialDoor.screenVertex.rightTop.y),
		static_cast<int>(ss->tutorialDoor.screenVertex.leftBottom.x),
		static_cast<int>(ss->tutorialDoor.screenVertex.leftBottom.y),
		static_cast<int>(ss->tutorialDoor.screenVertex.rightBottom.x),
		static_cast<int>(ss->tutorialDoor.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, BLACK);

	// ステージ1の描画処理
	Novice::DrawQuad(static_cast<int>(ss->stageOneDoor.screenVertex.leftTop.x),
		static_cast<int>(ss->stageOneDoor.screenVertex.leftTop.y),
		static_cast<int>(ss->stageOneDoor.screenVertex.rightTop.x),
		static_cast<int>(ss->stageOneDoor.screenVertex.rightTop.y),
		static_cast<int>(ss->stageOneDoor.screenVertex.leftBottom.x),
		static_cast<int>(ss->stageOneDoor.screenVertex.leftBottom.y),
		static_cast<int>(ss->stageOneDoor.screenVertex.rightBottom.x),
		static_cast<int>(ss->stageOneDoor.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, RED);

	// ステージ2の描画処理
	Novice::DrawQuad(static_cast<int>(ss->stageTwoDoor.screenVertex.leftTop.x),
		static_cast<int>(ss->stageTwoDoor.screenVertex.leftTop.y),
		static_cast<int>(ss->stageTwoDoor.screenVertex.rightTop.x),
		static_cast<int>(ss->stageTwoDoor.screenVertex.rightTop.y),
		static_cast<int>(ss->stageTwoDoor.screenVertex.leftBottom.x),
		static_cast<int>(ss->stageTwoDoor.screenVertex.leftBottom.y),
		static_cast<int>(ss->stageTwoDoor.screenVertex.rightBottom.x),
		static_cast<int>(ss->stageTwoDoor.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, WHITE);

	// ステージ3の描画処理
	Novice::DrawQuad(static_cast<int>(ss->stageThreeDoor.screenVertex.leftTop.x),
		static_cast<int>(ss->stageThreeDoor.screenVertex.leftTop.y),
		static_cast<int>(ss->stageThreeDoor.screenVertex.rightTop.x),
		static_cast<int>(ss->stageThreeDoor.screenVertex.rightTop.y),
		static_cast<int>(ss->stageThreeDoor.screenVertex.leftBottom.x),
		static_cast<int>(ss->stageThreeDoor.screenVertex.leftBottom.y),
		static_cast<int>(ss->stageThreeDoor.screenVertex.rightBottom.x),
		static_cast<int>(ss->stageThreeDoor.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, BLUE);

	DrawPlayer(player);


	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ss->fadeColor, kFillModeSolid);

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
	ss->fadeIn.startColor = opaque;
	ss->fadeOut.startColor = transparent;
	ss->isNextScene = false;


	InitPlayer(player, map);

	ss->tutorialDoor.pos.x = 640.0f;
	ss->tutorialDoor.pos.y = 300.0f;
	ss->tutorialDoor.width = 100.0f;
	ss->tutorialDoor.height = 100.0f;

	CalcVertexRectangle(&ss->tutorialDoor);
	ConvertWorldToScreenRectangle(&ss->tutorialDoor);

	ss->stageOneDoor.pos.x = 190.0f;
	ss->stageOneDoor.pos.y = 350.0f;
	ss->stageOneDoor.width = 100.0f;
	ss->stageOneDoor.height = 100.0f;

	CalcVertexRectangle(&ss->stageOneDoor);
	ConvertWorldToScreenRectangle(&ss->stageOneDoor);

	ss->stageTwoDoor.pos.x = 640.0f;
	ss->stageTwoDoor.pos.y = 600.0f;
	ss->stageTwoDoor.width = 100.0f;
	ss->stageTwoDoor.height = 100.0f;

	CalcVertexRectangle(&ss->stageTwoDoor);
	ConvertWorldToScreenRectangle(&ss->stageTwoDoor);

	ss->stageThreeDoor.pos.x = 1100.0f;
	ss->stageThreeDoor.pos.y = 350.0f;
	ss->stageThreeDoor.width = 100.0f;
	ss->stageThreeDoor.height = 100.0f;

	CalcVertexRectangle(&ss->stageThreeDoor);
	ConvertWorldToScreenRectangle(&ss->stageThreeDoor);


}
#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Boss.h"
#include "Particle.h"
#include "Rectangle.h"
#include "Matrix.h"

//========================================================
// プレイシーンの更新処理
//========================================================

Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm, Boss* boss, SelectScene* ss, Map* map)
{
	Scene nextScene = Play;

	if (ps->fadeIn.isEase)
	{
		ColorLinearInterpolation(ps->fadeIn.startColor, transparent, ps->fadeColor, ps->fadeIn);
		CountEaseInOutTimer(ps->fadeIn);
	}
	else
	{
		if (ps->fadeInBossT1.isEase)
		{
			LinearInterpolation(ps->fadeInBossT1.floatStartPos, 600.0f, boss->T1.pos.y, ps->fadeInBossT1);
			CountEaseInOutTimer(ps->fadeInBossT1);
		
			CalcVertexRectangle(&boss->T1);
			ConvertWorldToScreenRectangle(&boss->T1);

			if (!ps->fadeInBossT1.isEase)
			{
				ps->fadeInBossT1Particle->isEmit = true;
			}
		}

		else
		{
			if (ps->fadeInBossT1Particle->isEmit)
			{
				UpdateGoUpGravityParticle(ps->fadeInBossT1Particle, &boss->T1.pos);
				boss->T1.canMove = true;
			}
			else
			{

				UpdateMoveBoss(boss, player);
				MovePlayer(player, gm);

				if (player->knockback.isKnockbacked)
				{
					if (player->HP == 0 || player->HP == 1)
					{
						ps->playerHpEffectEase[0].isEase = true;
					}
					else if (player->HP == 2 || player->HP == 3)
					{
						ps->playerHpEffectEase[1].isEase = true;
					}
					else if (player->HP == 4 || player->HP == 5)
					{
						ps->playerHpEffectEase[2].isEase = true;
					}
				}

				for (int i = 0; i < 3; ++i)
				{
					ps->playerHpIcon[i].theta += 1.0f / 100.0f * static_cast<float>(M_PI);

					ps->playerHpIconEffect[i].pos.y = 650.0f + cosf(ps->playerHpIcon[i].theta) * 10.0f;

					if (ps->playerHpEffectEase[i].isEase)
					{
						ColorLinearInterpolation(ps->playerHpEffectEase[i].startColor, ps->playerHpEffectEase[i].endColor, ps->playerHpIconEffect[i].color, ps->playerHpEffectEase[i]);
						LinearInterpolation(ps->playerHpEffectEase[i].vec2StartPos, ps->playerHpEffectEase[i].vec2EndPos, ps->playerHpIconEffect[i].scale, ps->playerHpEffectEase[i]);
						CountEaseOutTimer(ps->playerHpEffectEase[i]);

						if (!ps->playerHpEffectEase[i].isEase)
						{
							ps->playerHpEffectOutEase[i].isEase = true;
						}
					}

					if (ps->playerHpEffectOutEase[i].isEase)
					{
						ColorLinearInterpolation(ps->playerHpEffectOutEase[i].startColor, ps->playerHpEffectOutEase[i].endColor, ps->playerHpIconEffect[i].color, ps->playerHpEffectOutEase[i]);
						CountEaseInOutTimer(ps->playerHpEffectOutEase[i]);
					}

					CalcVertexRectangle(&ps->playerHpIconEffect[i]);
					ConvertWorldToScreenRectangle(&ps->playerHpIconEffect[i]);

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
						ColorLinearInterpolation(ps->fadeOut.startColor, opaque, ps->fadeColor, ps->fadeOut);
						CountEaseInOutTimer(ps->fadeOut);

					}
					else
					{
						InitSelectScene(ss, player, map);
						nextScene = Select;
					}
				}
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
			static_cast<int>(ps->playerHpIcon[i].screenVertex.leftBottom.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.leftBottom.y),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightBottom.x),
			static_cast<int>(ps->playerHpIcon[i].screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ps->playerHpIcon[i].color);

		Novice::DrawQuad(
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.leftTop.x),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.leftTop.y),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.rightTop.x),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.rightTop.y),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.leftBottom.x),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.leftBottom.y),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.rightBottom.x),
			static_cast<int>(ps->playerHpIconEffect[i].screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ps->playerHpIconEffect[i].color);

		DrawGoUpGravityParticle(ps->fadeInBossT1Particle);
	}


	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ps->fadeColor, kFillModeSolid);

	Novice::ScreenPrintf(0, 0, "HP : %d", player->HP);
	Novice::ScreenPrintf(0, 20, "%d", boss->T1.impactDustParticle->isEmit);
	
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
	ps->fadeIn.startColor = opaque;
	ps->fadeOut.startColor = transparent;
	ps->fadeInBossT1.isEase = true;
	ps->fadeInBossT1.interval = 0.005f;
	ps->fadeInBossT1.floatStartPos = 750.0f;

	//パーティクルに関する初期化
	ps->fadeInBossT1Particle->amount = 32;

	InitGoUpGravityParticle(ps->fadeInBossT1Particle);

	ps->isNextScene = false;



	for (int i = 0; i < 3; ++i)
	{
		ps->playerHpIcon[i].pos.x = static_cast<float>(100 + i * 70);
		ps->playerHpIcon[i].pos.y = 650;

		ps->playerHpIcon[i].width = 50;
		ps->playerHpIcon[i].height = 50;

		ps->playerHpIcon[i].color = 0xff0000dd;

		ps->playerHpIcon[i].scale = {1.0f,1.0f };

		ps->playerHpIconEffect[i].pos.x = static_cast<float>(100 + i * 70);
		ps->playerHpIconEffect[i].pos.y = 650;

		ps->playerHpIconEffect[i].width = 70;
		ps->playerHpIconEffect[i].height = 70;

		ps->playerHpIconEffect[i].scale = { 0.0f,0.0f };

		ps->playerHpEffectEase[i].isEase = false;

		ps->playerHpEffectEase[i].vec2StartPos = { 0.0f,0.0f };
		ps->playerHpEffectEase[i].vec2EndPos = { 1.0f,1.0f };
		ps->playerHpEffectEase[i].startColor = 0xffffff00;
		ps->playerHpEffectEase[i].endColor = 0xffffffbb;
		ps->playerHpEffectEase[i].interval = 0.02f;

		ps->playerHpEffectOutEase[i].startColor = 0xffffffbb;
		ps->playerHpEffectOutEase[i].endColor = 0xffffff00;
		ps->playerHpEffectOutEase[i].interval = 0.02f;


		ps->playerHpIconEffect[i].color = 0xffffff00;

		CalcVertexRectangle(&ps->playerHpIcon[i]);
		ConvertWorldToScreenRectangle(&ps->playerHpIcon[i]);

		CalcVertexRectangle(&ps->playerHpIconEffect[i]);
		ConvertWorldToScreenRectangle(&ps->playerHpIconEffect[i]);

	}

	

	InitBoss(boss, map);
	InitPlayer(player, map);

	InitCenterToAroundParticle(boss->T1.aroundParticle);
	InitLikeSmokeParticle(player->likeSmokeParticle);
	Novice::SetJoystickDeadZone(0, 8000, 8000); // 左右スティックのデッドゾーンを設定
}


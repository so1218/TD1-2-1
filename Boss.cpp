#include "Structures.h"
#include "Rectangle.h"
#include "Easing.h"
#include "Calculate.h"
#include "Boss.h"
#include "Particle.h"
#include "BossAction.h"
#include "Hit.h"

//========================================================
// ボスの更新処理
//========================================================

void UpdateMoveBoss(Boss* boss, Player* player)
{
	UpdateMoveBossT1(boss, player);
}



void UpdateMoveBossT1(Boss* boss, Player* player)
{
	CalcVertexRectangle(&boss->T1);
	ConvertWorldToScreenRectangle(&boss->T1);

	// 距離に基づいてインターバル変更
	if (boss->T1.toPlayerDir < 200.0f)
	{
		boss->T1.MoveEase.interval = 0.000002f;
	}
	else if (boss->T1.toPlayerDir < 400.0f)
	{
		boss->T1.MoveEase.interval = 0.000008f;
	}
	else
	{
		boss->T1.MoveEase.interval = 0.00001f;
	}

	
	// フレームごとにランダムに攻撃方法を選ぶ
	if (boss->T1.actionFrameCounter >= 200)
	{
		// ランダムに選択
		boss->T1.randAction = rand() % 3;
		boss->T1.isAction = true;


		if (boss->T1.randAction == 0)
		{
			// FireSomewayDirectionBulletを呼び出し
			boss->T1.bulletSomeway->isAction = true;
			InitSomewayDirectionBullet(boss->T1.bulletSomeway);
		}
		else if(boss->T1.randAction == 1)
		{
			// FireToSomethingBulletを呼び出し
			boss->T1.bulletToPlayer->isAction = true;
			InitToSomethingBullet(boss->T1.bulletToPlayer);
		
		}
		else if (boss->T1.randAction == 2)
		{
			boss->T1.goUpParticle->isEmit = true;
			InitGoUpGravityParticle(boss->T1.goUpParticle);
		}

		// フレームカウンターをリセット
		boss->T1.actionFrameCounter = 0;
	}
	
	
	if (boss->T1.bulletSomeway->isAction)
	{
		FireSomewayDirectionBullet(boss->T1.bulletSomeway, boss->T1.pos);
	}
	else if (boss->T1.bulletToPlayer->isAction)
	{
		FireToSomethingBullet(boss->T1.bulletToPlayer, &boss->T1.pos, &player->pos);
	}
	else if (boss->T1.goUpParticle->isEmit)
	{
		UpdateGoUpGravityParticle(boss->T1.goUpParticle, &boss->T1.pos);
	}
	else
	{
		boss->T1.actionFrameCounter++;
	}

	UpdateCenterToAroundParticle(boss->T1.aroundParticle, &boss->T1.pos);
	/*UpdateImpactDustCloudParticle(boss->T1.impactDustParticle, &boss->T1.pos);*/
	
	//ノックバック判定
	KnockbackBossT1Func(boss, player);

	if (boss->T1.canMove)
	{
		LinearInterpolation(boss->T1.pos, player->pos, boss->T1.pos, boss->T1.MoveEase);
		CountEaseTimerMoveBossT1(boss->T1.MoveEase);
	}
}



//ボスT1とのノックバック判定
void KnockbackBossT1Func(Boss* boss, Player* player)
{
	//ノックバック判定
	ApplyKnockbackPlayer(&boss->T1.knockback, &boss->T1, player, &player->pos, &boss->T1.pos, player);

	if (CheckRectangleRectangleCollision(&boss->T1, player) && !player->knockback.isKnockbacked)
	{
		player->HP -= 1;

		player->knockback.isKnockbacked = true;
	}

	for (int i = 0; i < boss->T1.goUpParticle->amount; ++i)
	{
		ApplyKnockbackPlayer(&boss->T1.goUpParticle[i].knockback, &boss->T1.goUpParticle[i], player, &player->pos, &boss->T1.goUpParticle[i].pos, player);

		if (CheckRectangleRectangleCollision(&boss->T1.goUpParticle[i], player) && !player->knockback.isKnockbacked)
		{
			player->HP -= 1;

			player->knockback.isKnockbacked = true;
			break;
		}
	}

	for (int i = 0; i < boss->T1.bulletToPlayer->amount; ++i)
	{

		ApplyKnockbackPlayer(&boss->T1.bulletToPlayer[i].knockback, &boss->T1.bulletToPlayer[i], player, &player->pos, &boss->T1.bulletToPlayer[i].pos, player);

		if (CheckRectangleRectangleCollision(&boss->T1.bulletToPlayer[i], player) && !player->knockback.isKnockbacked)
		{
			player->HP -= 1;

			player->knockback.isKnockbacked = true;
			break;
		}
	}

	for (int i = 0; i < boss->T1.bulletSomeway->amount; ++i)
	{

		ApplyKnockbackPlayer(&boss->T1.bulletSomeway[i].knockback, &boss->T1.bulletSomeway[i], player, &player->pos, &boss->T1.bulletSomeway[i].pos, player);


		if (CheckRectangleRectangleCollision(&boss->T1.bulletSomeway[i], player) && !player->knockback.isKnockbacked)
		{
			player->HP -= 1;

			player->knockback.isKnockbacked = true;
			break;
		}
	}

	if (player->knockback.isKnockbacked)
	{
		player->knockback.frameCount++;
		player->color = 0xf69922ff;
	}
	else
	{
		player->color = 0x0000ffff;
	}

	if (player->knockback.frameCount >= 50)
	{
		player->knockback.isKnockbacked = false;
		player->knockback.frameCount = 0;
	}
}

//========================================================
// ボスの描画処理
//========================================================

void DrawBoss(Boss* boss)
{
	Novice::DrawQuad(
		static_cast<int>(boss->T1.screenVertex.leftTop.x),
		static_cast<int>(boss->T1.screenVertex.leftTop.y),
		static_cast<int>(boss->T1.screenVertex.rightTop.x),
		static_cast<int>(boss->T1.screenVertex.rightTop.y),
		static_cast<int>(boss->T1.screenVertex.leftBottom.x),
		static_cast<int>(boss->T1.screenVertex.leftBottom.y),
		static_cast<int>(boss->T1.screenVertex.rightBottom.x),
		static_cast<int>(boss->T1.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, boss->T1.color);

	DrawCenterToAroundParticle(boss->T1.aroundParticle);
	DrawGoUpGravityParticle(boss->T1.goUpParticle);
	DrawImpactDustCloudParticle(boss->T1.impactDustParticle);

	DrawSomewayDirectionBullet(boss->T1.bulletSomeway);
	DrawToSomethingBullet(boss->T1.bulletToPlayer);

	Novice::ScreenPrintf(20, 100, "%d", boss->T1.knockback.isKnockback);
}

//========================================================
// ボスの初期化
//========================================================

void InitBoss(Boss* boss, Map* map)
{
	//ボス1の初期位置初期化
	boss->T1.startChipNo = { 6, 8 };

	boss->T1.radius = { 25.0f, 25.0f };
	boss->T1.velocity = { 5.0f, 5.0f };

	boss->T1.width = 50;
	boss->T1.height = 50;
	boss->T1.color = RED;

	//パーティクルに関する初期化
	boss->T1.aroundParticle->amount = 16;
	boss->T1.goUpParticle->amount = 32;
	boss->T1.impactDustParticle->amount = 10;
	InitGoUpGravityParticle(boss->T1.goUpParticle);
	InitImpactDustCloudParticle(boss->T1.impactDustParticle);

	boss->T1.MoveEase.interval = 0.000005f;

	//弾に関する初期化
	InitSomewayDirectionBullet(boss->T1.bulletSomeway);
	InitToSomethingBullet(boss->T1.bulletToPlayer);
	boss->T1.bulletSomeway->amount = 16;
	boss->T1.bulletToPlayer->amount = 16;
	

	

	//開始位置座標

	//初期位置チップナンバー
	if (map->stageNo == 0)
	{
		boss->T1.startChipNo.x = 3;
		boss->T1.startChipNo.y = 3;
	}

	else if (map->stageNo == 1)
	{
		boss->T1.startChipNo.x = 9;
		boss->T1.startChipNo.y = 8;
	}

	else if (map->stageNo == 2)
	{
		boss->T1.startChipNo.x = 10;
		boss->T1.startChipNo.y = 6;
	}

	else if (map->stageNo == 3)
	{
		boss->T1.startChipNo.x = 10;
		boss->T1.startChipNo.y = 8;
	}

	boss->T1.pos = { kWindowWidth / 2,800 };

	boss->T1.currentChipNo = boss->T1.startChipNo;
	boss->T1.prePos = boss->T1.pos;

	CalcVertexRectangle(&boss->T1);
	ConvertWorldToScreenRectangle(&boss->T1);

	
}
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

	if (CheckRectangleRectangleCollision(&boss->T1, player))
	{

		boss->T1.knockbackDir = { player->pos.x - boss->T1.pos.x, player->pos.y - boss->T1.pos.y };

		boss->T1.knockbackNormalizedDir = CalculateNormalize(boss->T1.knockbackDir);

		boss->T1.knockback.velocity.x = boss->T1.knockbackNormalizedDir.x * boss->T1.knockbackStrength;
		boss->T1.knockback.velocity.y = boss->T1.knockbackNormalizedDir.y * boss->T1.knockbackStrength;

		boss->T1.isKnockback = true;
		

	}

	if(boss->T1.isKnockback)
	{
		boss->T1.knockback.velocity.x *= 0.95f;
		boss->T1.knockback.velocity.y *= 0.95f;
		player->pos.x += boss->T1.knockback.velocity.x;
		player->pos.y += boss->T1.knockback.velocity.y;
	}
	if (fabs(boss->T1.knockback.velocity.x) < 0.1f || fabs(boss->T1.knockback.velocity.y) < 0.1f)
	{
		boss->T1.isKnockback = false;
		boss->T1.knockback.velocity.x = 0.0f;
		boss->T1.knockback.velocity.y = 0.0f;
	}
	

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
		boss->T1.randAction = rand() % 2;
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
	else
	{
		boss->T1.actionFrameCounter++;
	}

	UpdateCenterToAroundParticle(boss->T1.aroundParticle, &boss->T1.pos);
	UpdateGoUpGravityParticle(boss->T1.goUpParticle, &boss->T1.pos);
	UpdateImpactDustCloudParticle(boss->T1.impactDustParticle, &boss->T1.pos);
	

	LinearInterpolation(boss->T1.pos, player->pos, boss->T1.pos, boss->T1.MoveEase);
	CountEaseTimerMoveBossT1(boss->T1.MoveEase);
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
		static_cast<int>(boss->T1.screenVertex.lehtBottom.x),
		static_cast<int>(boss->T1.screenVertex.lehtBottom.y),
		static_cast<int>(boss->T1.screenVertex.rightBottom.x),
		static_cast<int>(boss->T1.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, boss->T1.color);

	DrawCenterToAroundParticle(boss->T1.aroundParticle);
	DrawGoUpGravityParticle(boss->T1.goUpParticle);
	DrawImpactDustCloudParticle(boss->T1.impactDustParticle);
	

	DrawSomewayDirectionBullet(boss->T1.bulletSomeway);
	DrawToSomethingBullet(boss->T1.bulletToPlayer);

	Novice::ScreenPrintf(20, 100, "%d", boss->T1.isKnockback);
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

	else if (map->stageNo == 4)
	{
		boss->T1.startChipNo.x = 7;
		boss->T1.startChipNo.y = 9;
	}

	else if (map->stageNo == 5)
	{
		boss->T1.startChipNo.x = 10;
		boss->T1.startChipNo.y = 6;
	}

	else if (map->stageNo == 6)
	{
		boss->T1.startChipNo.x = 9;
		boss->T1.startChipNo.y = 8;
	}

	else if (map->stageNo == 7)
	{
		boss->T1.startChipNo.x = 10;
		boss->T1.startChipNo.y = 5;
	}

	else if (map->stageNo == 8)
	{
		boss->T1.startChipNo.x = 9;
		boss->T1.startChipNo.y = 9;
	}

	else if (map->stageNo == 9)
	{
		boss->T1.startChipNo.x = 13;
		boss->T1.startChipNo.y = 4;
	}

	boss->T1.pos = map->chip[boss->T1.startChipNo.y][boss->T1.startChipNo.x].pos;

	boss->T1.currentChipNo = boss->T1.startChipNo;
	boss->T1.prePos = boss->T1.pos;

	CalcVertexRectangle(&boss->T1);
	ConvertWorldToScreenRectangle(&boss->T1);

	
}
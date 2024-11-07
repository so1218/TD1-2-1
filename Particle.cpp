#include "Structures.h"
#include "Vector.h"
#include "PhysicalElements.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "Easing.h"
#include "BezierCurve.h"
#include <stdlib.h>

//中心から周囲にEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateCenterToAroundParticle(Particle* particle, Vector2* startPos)
{
	if (particle->frameCount <= 0)
	{
		particle->frameCount = particle->appearInterval;
	}

	// フレームごとに新しいパーティクルを生成
	if (particle->frameCount == particle->appearInterval)
	{
		for (int i = 0; i < particle->amount; ++i)
		{

			if (!particle[i].isExist)
			{
				// フレームごとに新しいパーティクルを生成
				if (particle->frameCount % 2 == 0 && particle->frameCount / 2 > i)
				{

					particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
					particle[i].pos.x = static_cast<float>(startPos->x);
					particle[i].pos.y = static_cast<float>(startPos->y);

					particle[i].speed = { 1.0f,1.0f };
					particle[i].velocity.x = particle->speed.x * cosf(particle->angle);
					particle[i].velocity.y = particle->speed.y * sinf(particle->angle);

					particle[i].isExist = true;
					particle[i].easingInOut.isEase = true;

					break;
				}
			}
		}
	}

	particle->frameCount -= 1;

	for (int i = 0; i < particle->amount; ++i)
	{
		if (particle[i].isExist)
		{
			particle[i].pos.x += particle[i].velocity.x;
			particle[i].pos.y += particle[i].velocity.y;


			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
			}

			ColorLinearInterpolation(0xff0000ff, 0xff000000, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	}
}

void DrawCenterToAroundParticle(Particle* particle)
{
	

	for (int i = 0; i < particle->amount ; i++)
	{
		if (particle[i].isExist)
		{
			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.lehtBottom.x),
				static_cast<int>(particle[i].screenVertex.lehtBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 0, 0, 0, particle[i].color);
		}
	};

}

void InitCenterToAroundParticle(Particle* particle)
{
	
	for (int i = 0; i < particle->amount; ++i) 
	{

		particle[i].width = 10;
		particle[i].height = 10;
		
		particle[i].isExist = false;

	}

}
	

//上に向かって周囲にEmitterRangeの範囲で発生するパーティクル
void UpdateGoUpAroundParticle(Particle* particle, Vector2* startPos)
{
	
	if (particle->frameCount <= 0)
	{
		particle->frameCount = particle->appearInterval;
	}

	// フレームごとに新しいパーティクルを生成
	if (particle->frameCount == particle->appearInterval)
	{
		for (int i = 0; i < particle->amount; ++i)
		{

			if (!particle[i].isExist)
			{
				
				particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);
				particle[i].initialPos.y = particle[i].pos.y;
				particle[i].speed = { 1.0f,0.5f };
				particle[i].velocity.y = particle->speed.y;
				particle[i].isExist = true;
				particle[i].easingOut.isEase = true;
				particle[i].easingInOut.isEase = true;

				break;
			}
		}
	}

	particle->frameCount -= 1;

	for (int i = 0; i < particle->amount; ++i)
	{

		if (particle[i].isExist)
		{


			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
			}

			LinearInterpolation(particle[i].initialPos.y,
				particle[i].initialPos.y + particle->activeDistance.y,
				particle[i].pos.y,
				particle[i].easingOut);
			CountEaseOutTimer(particle[i].easingOut);

			ColorLinearInterpolation(0x0000ffff, 0x0000ff00, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	
	}
}

void DrawGoUpAroundParticle(Particle* particle)
{
	for (int i = 0; i < particle->amount; i++)
	{
		if (particle[i].isExist)
		{
			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.lehtBottom.x),
				static_cast<int>(particle[i].screenVertex.lehtBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 0, 0, 0, particle[i].color);
		}
	};

}

void InitGoUpAroundParticle(Particle* particle)
{

	for (int i = 0; i < particle->amount; ++i)
	{

		particle[i].width = 10;
		particle[i].height = 10;

		particle[i].isExist = false;

	}

}




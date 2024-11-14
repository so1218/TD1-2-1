#include "Structures.h"
#include "Vector.h"
#include "PhysicalElements.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "Easing.h"
#include "BezierCurve.h"
#include "Calculate.h"
#include <stdlib.h>
#include "BlendMode.h"
#include "GrovalTextureHandles.h"

//中心から周囲に向かうEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
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
				

				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = static_cast<float>(startPos->x);
				particle[i].pos.y = static_cast<float>(startPos->y);

				particle[i].speed = { 1.0f,1.0f };
				particle[i].velocity.x = particle->speed.x * cosf(particle->angle);
				particle[i].velocity.y = particle->speed.y * sinf(particle->angle);

				particle[i].isExist = true;
				particle[i].easingInOut.isEase = true;

				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

				break;
				
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
			UpdateBlendMode(&particle[i].blendMode);


			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 64, 64, GHs[TextureName::Particle1], particle[i].color);

			ResetBlendMode();
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

		particle[i].blendMode.choiceType = particle->blendMode.Add;
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
				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

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
			UpdateBlendMode(&particle[i].blendMode);

			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 0, 0, 0, particle[i].color);

			ResetBlendMode();
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

//進行方向と逆に出る動いているときの煙のようなパーティクル
void UpdateLikeSmokeParticle(Particle* particle, Vector2* startPos)
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
				

				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);

				particle[i].speed = { 0.2f,0.2f };
				particle[i].velocity.x = particle->speed.x * cosf(particle->angle);
				particle[i].velocity.y = particle->speed.y * sinf(particle->angle);

				particle[i].isExist = true;
				particle[i].easingInOut.isEase = true;
				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

				break;
				
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

void DrawLikeSmokeParticle(Particle* particle)
{

	for (int i = 0; i < particle->amount; i++)
	{
		if (particle[i].isExist)
		{
			UpdateBlendMode(&particle[i].blendMode);

			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 64, 64, GHs[TextureName::Particle1], particle[i].color);

			ResetBlendMode();
		}
	};
}

void InitLikeSmokeParticle(Particle* particle)
{
	particle->appearInterval = 4;
	particle->emitterRange = { 20,20 };
	for (int i = 0; i < particle->amount; ++i)
	{
		particle[i].easingInOut.interval = 0.01f;
		particle[i].width = 10;
		particle[i].height = 10;

		particle[i].isExist = false;

	}

}

// 一気に上に行って重力を受けるパーティクル
void UpdateGoUpGravityParticle(Particle* particle, Vector2* startPos)
{

	// フレームごとに新しいパーティクルを生成
	
	for (int i = 0; i < particle->amount; ++i)
	{
		if (!particle[i].hasExisted)
		{
			if (!particle[i].isExist)
			{
				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);

				if (particle[i].pos.x >= startPos->x)
				{
					particle[i].speed = { static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f,static_cast<float>(rand()) / RAND_MAX * 4.0f + 8.0f };
				}
				else
				{
					particle[i].speed = { -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f,static_cast<float>(rand()) / RAND_MAX * 4.0f + 8.0f };
				}
				particle[i].velocity.x = particle[i].speed.x;
				particle[i].velocity.y = particle[i].speed.y;

				particle[i].isExist = true;
				particle[i].hasExisted = true;
				particle[i].easingInOut.isEase = true;

				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

			}
		}
	}
	

	for (int i = 0; i < particle->amount; ++i)
	{
		if (particle[i].isExist)
		{
			particle[i].pos.x += particle[i].velocity.x;
			particle[i].pos.y += particle[i].velocity.y;
			particle[i].velocity.y -= particle->gravity;

			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
				particle->isEmit = false;
			}

			ColorLinearInterpolation(0xff0000ff, 0xff000000, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	}
}

void DrawGoUpGravityParticle(Particle* particle)
{
	for (int i = 0; i < particle->amount; i++)
	{
		if (particle[i].isExist)
		{
			UpdateBlendMode(&particle[i].blendMode);

			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 64, 64, GHs[TextureName::Particle1], particle[i].color);

			ResetBlendMode();
		}
	};
}

void InitGoUpGravityParticle(Particle* particle)
{
	
	particle->emitterRange = { 40,40 };
	for (int i = 0; i < particle->amount; ++i)
	{
		
		particle[i].width = 10;
		particle[i].height = 10;

		particle[i].isExist = false;
		particle[i].hasExisted = false;
	}

}

// 一気に中心から外側に行くパーティクル
void UpdateImpactDustCloudParticle(Particle* particle, Vector2* startPos)
{

	// フレームごとに新しいパーティクルを生成

	for (int i = 0; i < particle->amount; ++i)
	{
		if (!particle[i].hasExisted)
		{
			if (!particle[i].isExist)
			{
				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);

				if (particle[i].pos.x >= startPos->x)
				{
					particle[i].speed.x = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
				}
				else
				{
					particle[i].speed.x = -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
				}

				if (particle[i].pos.y >= startPos->y)
				{
					particle[i].speed.y = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
				}
				else
				{
					particle[i].speed.y = -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
				}

				particle[i].velocity.x = particle[i].speed.x;
				particle[i].velocity.y = particle[i].speed.y;

				particle->gravity = 0.2f;

				particle[i].isExist = true;
				particle[i].hasExisted = true;
				particle[i].easingInOut.isEase = true;
				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

			}
		}
	}


	for (int i = 0; i < particle->amount; ++i)
	{
		if (particle[i].isExist)
		{
			particle[i].pos.x += particle[i].velocity.x;
			particle[i].pos.y += particle[i].velocity.y;
			particle[i].velocity.y -= particle->gravity;

			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
				particle->isEmit = false;
			}

			ColorLinearInterpolation(0xff00ffff, 0xff00ff00, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	}
}

void DrawImpactDustCloudParticle(Particle* particle)
{
	for (int i = 0; i < particle->amount; i++)
	{
		if (particle[i].isExist)
		{
			UpdateBlendMode(&particle[i].blendMode);

			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 0, 0, 0, particle[i].color);

			ResetBlendMode();
		}
	};
}

void InitImpactDustCloudParticle(Particle* particle)
{

	particle->emitterRange = { 60,40 };
	for (int i = 0; i < particle->amount; ++i)
	{
		particle[i].easingInOut.interval = 0.01f;
		particle[i].width = 10;
		particle[i].height = 10;

		particle[i].isExist = false;

	}

}

//周囲から中心に向かうEmitterRangeの範囲で発生するパーティクル
void UpdateToCenterParticle(Particle* particle, Vector2* startPos)
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


				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);

				
				particle[i].isExist = true;
				particle[i].easingInOut.isEase = true;
				particle[i].easingIn.isEase = true;
				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

				break;

			}
		}
	}

	particle->frameCount -= 1;

	for (int i = 0; i < particle->amount; ++i)
	{
		if (particle[i].isExist)
		{
			LinearInterpolation(particle[i].pos,
				*startPos,
				particle[i].pos,
				particle[i].easingIn);
			CountEaseOutTimer(particle[i].easingIn);


			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
			}

			ColorLinearInterpolation(0xff6ff4ff, 0xff000000, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	}
}

void DrawToCenterParticle(Particle* particle)
{
	for (int i = 0; i < particle->amount; i++)
	{
		if (particle[i].isExist)
		{
			UpdateBlendMode(&particle[i].blendMode);

			Novice::DrawQuad(
				static_cast<int>(particle[i].screenVertex.leftTop.x),
				static_cast<int>(particle[i].screenVertex.leftTop.y),
				static_cast<int>(particle[i].screenVertex.rightTop.x),
				static_cast<int>(particle[i].screenVertex.rightTop.y),
				static_cast<int>(particle[i].screenVertex.leftBottom.x),
				static_cast<int>(particle[i].screenVertex.leftBottom.y),
				static_cast<int>(particle[i].screenVertex.rightBottom.x),
				static_cast<int>(particle[i].screenVertex.rightBottom.y),
				0, 0, 0, 0, 0, particle[i].color);

			ResetBlendMode();
		}
	};
}

void InitToCenterParticle(Particle* particle)
{
	particle->emitterRange = { 150,150 };
	for (int i = 0; i < particle->amount; ++i)
	{
		particle[i].easingInOut.interval = 0.01f;
		particle[i].easingIn.interval = 0.0000005f;
		particle[i].width = 10;
		particle[i].height = 10;
		
		particle[i].isExist = false;

	}

}

// 隕石のようなパーティクル
void UpdateMateoriteParticle(Particle* particle, Vector2* startPos)
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

				particle->angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
				particle[i].pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle->emitterRange.x - particle->emitterRange.x / 2);
				particle[i].pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle->emitterRange.y - particle->emitterRange.y / 2);

				particle[i].isExist = true;
				particle[i].easingInOut.isEase = true;
				particle[i].easingIn.isEase = true;
				particle[i].blendMode.mode = particle[i].blendMode.choiceType;

				break;

			}
		}
	}

	particle->frameCount -= 1;

	for (int i = 0; i < particle->amount; ++i)
	{
		if (particle[i].isExist)
		{
			LinearInterpolation(particle[i].pos,
				*startPos,
				particle[i].pos,
				particle[i].easingIn);
			CountEaseOutTimer(particle[i].easingIn);


			if (!particle[i].easingInOut.isEase)
			{
				particle[i].isExist = false;
			}

			ColorLinearInterpolation(0xff6ff4ff, 0xff000000, particle[i].color, particle[i].easingInOut);
			CountEaseInOutTimer(particle[i].easingInOut);
		}

		CalcVertexRectangle(&particle[i]);
		ConvertWorldToScreenRectangle(&particle[i]);

	}
}
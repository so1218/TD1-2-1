#pragma once

#include "Structures.h"
#include "PhysicalElements.h"

//中心から周囲にEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateCenterToAroundParticle(Particle* particle, Vector2* startPos);
void DrawCenterToAroundParticle(Particle* particle);
void InitCenterToAroundParticle(Particle* particle);

//上に向かって周囲にEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateGoUpAroundParticle(Particle* particle, Vector2* startPos);
void DrawGoUpAroundParticle(Particle* particle);
void InitGoUpAroundParticle(Particle* particle);

//進行方向と逆に出る動いているときの煙のようなパーティクル
void UpdateLikeSmokeParticle(Particle* particle, Vector2* startPos);
void DrawLikeSmokeParticle(Particle* particle);
void InitLikeSmokeParticle(Particle* particle);

// 一気に上に行って重力を受けるパーティクル
void UpdateGoUpGravityParticle(Particle* particle, Vector2* startPos);
void DrawGoUpGravityParticle(Particle* particle);
void InitGoUpGravityParticle(Particle* particle);

// 一気に中心から外側に行くパーティクル
void UpdateImpactDustCloudParticle(Particle* particle, Vector2* startPos);
void DrawImpactDustCloudParticle(Particle* particle);
void InitImpactDustCloudParticle(Particle* particle);

//周囲から中心に向かうEmitterRangeの範囲で発生するパーティクル
void UpdateToCenterParticle(Particle* particle, Vector2* startPos);
void DrawToCenterParticle(Particle* particle);
void InitToCenterParticle(Particle* particle);
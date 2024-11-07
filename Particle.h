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
#pragma once

#include "Structures.h"

float EaseInCirc(const float& timer);
float EaseOutCirc(const float& timer);
float EaseInOutCirc(float timer);

// 線形補間
void ColorLinearInterpolation(const unsigned int start, const unsigned int end, unsigned int& current, const Easing& easing);

void LinearInterpolation(const int start, const int end, int& current, const Easing& easing);

void LinearInterpolation(const float start, const float end, float& current, const Easing& easing);

void LinearInterpolation(const Vector2& start, const Vector2& end, Vector2& current, const Easing& easing);

// イージングのタイマーカウント
void CountEaseTimer(Easing& easing);

void CountEaseTimer(const unsigned int end, unsigned int& current, Easing& easing);

void CountEaseTimer(const int end, int& current, Easing& easing);

void CountEaseTimer(const float end, float& current, Easing& easing);

void CountEaseTimer(const Vector2 end, Vector2& current, Easing& easing);

// イージングの初期化
void InitializeEasing(Easing& easing);

// イージングのデバッグ表示
void ScreenPrintfEasing(const int x, const int y, const Easing& easing);

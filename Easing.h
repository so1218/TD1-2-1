#pragma once

#include "Structures.h"

//イージングの関数
float EaseIn(const float& timer);
float EaseOut(const float& timer);
float EaseInOut(float timer);

// 線形補間

// 色遷移のイージング関数
void ColorLinearInterpolation(const unsigned int start, const unsigned int end, unsigned int& current, const Easing& easing);

void LinearInterpolation(const int start, const int end, int& current, const Easing& easing);

void LinearInterpolation(const float start, const float end, float& current, const Easing& easing);

void LinearInterpolation(const Vector2& start, const Vector2& end, Vector2& current, const Easing& easing);

// EaseInOutのイージングタイマー
void CountEaseInOutTimer(Easing& easing);

void CountEaseInOutTimer(const unsigned int end, unsigned int& current, Easing& easing);

void CountEaseInOutTimer(const int end, int& current, Easing& easing);

void CountEaseInOutTimer(const float end, float& current, Easing& easing);

void CountEaseInOutTimer(const Vector2 end, Vector2& current, Easing& easing);

void CountEaseTimerMoveBossT1(Easing& easing);

//EaseOutのイージングタイマー
void CountEaseOutTimer(Easing& easing);

// イージングの初期化
void InitializeEasing(Easing& easing);

// イージングのデバッグ表示
void ScreenPrintfEasing(const int x, const int y, const Easing& easing);

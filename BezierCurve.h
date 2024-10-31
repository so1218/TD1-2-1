#pragma once

#include "Structures.h"

// ベジェ曲線計算関数
float CalcBezierCurve(int count, int amount, float timer, unsigned int* pointer);

float CalcBezierCurve(int count, int amount, float timer, int* pointer);

float CalcBezierCurve(int count, int amount, float timer, float* pointer);

void CalcBezierCurve(int amount, float timer, Vector2* current, Vector2* pointer);

// 補間時間計算関数
void CountCurveTimer(const int amount, Easing* easing);

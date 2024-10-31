#include "Structures.h"
#include "Calc.h"
#include "Easing.h"

float CalcBezierCurve(int count, int amount, float timer, unsigned int* pointer) {
    if (count >= amount) {
        return 0.0f;
    }
    return static_cast<float>(pointer[count]) * Bernstein(amount - 1, count, timer) +
        CalcBezierCurve(count + 1, amount, timer, pointer);
}

float CalcBezierCurve(int count, int amount, float timer, int* pointer) {
    if (count >= amount) {
        return 0.0f;
    }
    return static_cast<float>(pointer[count]) * Bernstein(amount - 1, count, timer) +
        CalcBezierCurve(count + 1, amount, timer, pointer);
}

float CalcBezierCurve(int count, int amount, float timer, float* pointer) {
    if (count >= amount) {
        return 0.0f;
    }
    return pointer[count] * Bernstein(amount - 1, count, timer) +
        CalcBezierCurve(count + 1, amount, timer, pointer);
}

void CalcBezierCurve(int amount, float timer, Vector2* current, Vector2* pointer) {
    if (current == nullptr || pointer == nullptr) return; // nullptr チェック

    current->x = 0.0f;
    current->y = 0.0f;

    for (int i = 0; i < amount; i++) {
        current->x += pointer[i].x * Bernstein(amount - 1, i, timer);
        current->y += pointer[i].y * Bernstein(amount - 1, i, timer);
    }
}

void CountCurveTimer(const int amount, Easing* easing) {
    if (easing == nullptr) return; // nullptr チェック

    easing->cycle = 1.0f / (static_cast<float>(amount) / easing->interval);

    if (easing->timer > 1.0f) {
        easing->easeTimer = 0.0f;
        easing->timer = 0.0f;
        easing->isEase = false;
    }
    else {
        easing->timer += easing->cycle;
        easing->easeTimer = EaseInOutCirc(&easing->timer);
    }
}

#include "Structures.h"

float EaseInCirc(const float& timer) {

	return 1.0f - sqrtf(1.0f - timer * timer);

}

float EaseOutCirc(const float& timer) {

	return sqrtf(1.0f - (timer - 1.0f) * (timer - 1.0f));

}

float EaseInOutCirc(float timer) {

	timer *= 2;

	if (timer < 1) {
		return 0.5f * (1 - (float)sqrt(1 - timer * timer)); // easeIn
	}
	else {
		timer -= 2; // easeOutに移る
		return 0.5f * ((float)sqrt(1 - timer * timer) + 1); // easeOut
	}

}

void CountEaseTimer(Easing& easing) {

	if (easing.timer > 1.0f) {

		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOutCirc(easing.timer);

	}

}

void CountEaseTimer(const unsigned int end, unsigned int& current, Easing& easing) {

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOutCirc(easing.timer);

	}

}

void CountEaseTimer(const int end, int& current, Easing& easing) {

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOutCirc(easing.timer);

	}

}

void CountEaseTimer(const float end, float& current, Easing& easing) {

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOutCirc(easing.timer);

	}

}

void CountEaseTimer(const Vector2 end, Vector2& current, Easing& easing) {

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOutCirc(easing.timer);

	}

}

void LinearInterpolation(const unsigned int start, const unsigned int end, unsigned int& current, const Easing& easing) {

	//赤
	unsigned int startR = (start >> 24) & 0xff;

	//緑
	unsigned int startG = (start >> 16) & 0xff;

	//青
	unsigned int startB = (start >> 8) & 0xff;

	//透明度
	unsigned int startA = start & 0xff;

	unsigned int endR = (end >> 24) & 0xff;
	unsigned int endG = (end >> 16) & 0xff;
	unsigned int endB = (end >> 8) & 0xff;
	unsigned int endA = end & 0xff;

	// 各成分を補間
	unsigned int newR = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startR) + easing.easeTimer * static_cast<float>(endR));
	unsigned int newG = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startG) + easing.easeTimer * static_cast<float>(endG));
	unsigned int newB = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startB) + easing.easeTimer * static_cast<float>(endB));
	unsigned int newA = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startA) + easing.easeTimer * static_cast<float>(endA));

	current = (newR << 24) | (newG << 16) | (newB << 8) | newA;

}

void LinearInterpolation(const int start, const int end, int& current, const Easing& easing) {

	current = static_cast<int>((1.0f - easing.easeTimer) * static_cast<float>(start) + easing.easeTimer * static_cast<float>(end));

}

void LinearInterpolation(const float start, const float end, float& current, const Easing& easing) {

	current = (1.0f - easing.easeTimer) * start + easing.easeTimer * end;

}

void LinearInterpolation(const Vector2& start, const Vector2& end, Vector2& current, const Easing& easing) {

	LinearInterpolation(start.x, end.x, current.x, easing);
	LinearInterpolation(start.y, end.y, current.y, easing);

}

void InitializeEasing(Easing& easing) {

	easing.interval = 0.01f;
	easing.cycle = 0.0f;
	easing.timer = 0.0f;
	easing.easeTimer = 0.0f;
	easing.isEase = false;

}

void ScreenPrintfEasing(const int x, const int y, const Easing& easing) {

	Novice::ScreenPrintf(x, y, "interval : %f", easing.interval);
	Novice::ScreenPrintf(x, y + 20, "timer : %f", easing.timer);
	Novice::ScreenPrintf(x, y + 40, "easeTimer : %f", easing.easeTimer);
	Novice::ScreenPrintf(x, y + 60, "isEase : %d", easing.isEase);

}

#include "Structures.h"
#include "TitleScene.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Rectangle.h"
#include "Player.h"


//========================================================
// タイトルシーンの更新処理
//========================================================

Scene UpdateTitleScene(TitleScene* ts, SelectScene* ss, Player* player, Map* map)
{

	Scene nextScene = Title;

	if (ts->fadeIn.isEase)
	{
		ColorLinearInterpolation(ts->fadeIn.startColor, transparent, ts->fadeColor, ts->fadeIn);
		CountEaseInOutTimer(ts->fadeIn);

		if (!ts->fadeIn.isEase)
		{
			ts->titleOneEase.isEase = true;
		}
	}
	else
	{
		// タイトルロゴが1パーツずつイージングしてくる処理

		if (ts->titleOneEase.isEase)
		{
			LinearInterpolation(ts->titleOneStart, ts->titleOneEnd, ts->titleOne.pos, ts->titleOneEase);
			CountEaseOutTimer(ts->titleOneEase);

			if (ts->titleOneEase.easeTimer >= 0.5f)
			{
				ts->titleTwoEase.isEase = true;
			}

		}

		if (ts->titleTwoEase.isEase)
		{
			LinearInterpolation(ts->titleTwoStart, ts->titleTwoEnd, ts->titleTwo.pos, ts->titleTwoEase);
			CountEaseOutTimer(ts->titleTwoEase);

			if (ts->titleTwoEase.easeTimer >= 0.5f)
			{
				ts->titleThreeEase.isEase = true;
			}

		}

		if (ts->titleThreeEase.isEase)
		{
			LinearInterpolation(ts->titleThreeStart, ts->titleThreeEnd, ts->titleThree.pos, ts->titleThreeEase);
			CountEaseOutTimer(ts->titleThreeEase);

			if (ts->titleThreeEase.easeTimer >= 0.5f)
			{
				ts->titleFourEase.isEase = true;
			}

		}

		if (ts->titleFourEase.isEase)
		{
			LinearInterpolation(ts->titleFourStart, ts->titleFourEnd, ts->titleFour.pos, ts->titleFourEase);
			CountEaseOutTimer(ts->titleFourEase);

			if (ts->titleFourEase.easeTimer >= 0.9f)
			{
				ts->titleFadeOut.isEase = true;
			}

		}
		
		// タイトルロゴが完成したらフェードアウトさせる
		if (ts->titleFadeOut.isEase)
		{
			ColorLinearInterpolation(transparent, ts->titleFadeOut.endColor, ts->titleFadeColor, ts->titleFadeOut);
			CountEaseOutTimer(ts->titleFadeOut);
			ColorLinearInterpolation(ts->titleLogoFade.startColor, ts->titleLogoFade.endColor, ts->titleLogoColor, ts->titleLogoFade);
			CountEaseOutTimer(ts->titleLogoFade);

			if (!ts->titleFadeOut.isEase)
			{
				ts->titleFadeIn.isEase = true;
				ts->istitleLogoComplete = true;
			}

		}

		if (ts->titleFadeIn.isEase)
		{
			ColorLinearInterpolation(ts->titleFadeIn.startColor, transparent, ts->titleFadeColor, ts->titleFadeIn);
			CountEaseInTimer(ts->titleFadeIn);
		}

		// 座標更新のために再定義する
		CalcVertexRectangle(&ts->titleLogo);
		ConvertWorldToScreenRectangle(&ts->titleLogo);
		CalcVertexRectangle(&ts->titleOne);
		ConvertWorldToScreenRectangle(&ts->titleOne);
		CalcVertexRectangle(&ts->titleTwo);
		ConvertWorldToScreenRectangle(&ts->titleTwo);
		CalcVertexRectangle(&ts->titleThree);
		ConvertWorldToScreenRectangle(&ts->titleThree);
		CalcVertexRectangle(&ts->titleFour);
		ConvertWorldToScreenRectangle(&ts->titleFour);

		// タイトルロゴを上下させる
		ts->titleLogo.pos.y = sinf(ts->theta) * ts->amplitude;
		ts->theta += static_cast<float>(M_PI) / 30.0f;
		ts->titleLogo.pos.y += 500.0f;

		//次のシーンへのトリガー
		if (ts->gm->keys[DIK_SPACE] && !ts->gm->preKeys[DIK_SPACE])
		{
			ts->fadeOut.isEase = true;
			ts->isNextScene = true;
		}
		if (ts->isNextScene)
		{
			if (ts->fadeOut.isEase)
			{
				ColorLinearInterpolation(ts->fadeOut.startColor, opaque, ts->fadeColor, ts->fadeOut);
				CountEaseInOutTimer(ts->fadeOut);
			}
			else
			{
				InitSelectScene(ss, player, map);

				nextScene = Select;
			}
		}

	}

	return nextScene;

}

//========================================================
// タイトルシーンの描画処理
//========================================================

// タイトルシーンのデバック(デバックモードのみ)
void ScreenPrintfTitleScene()
{
	Novice::ScreenPrintf(0, 0, "Title");
}

//タイトルシーンの描画
void DrawTitleScene(TitleScene* ts)
{
	if (ts->istitleLogoComplete)
	{

		Novice::DrawQuad(
			static_cast<int>(ts->titleLogo.screenVertex.leftTop.x),
			static_cast<int>(ts->titleLogo.screenVertex.leftTop.y),
			static_cast<int>(ts->titleLogo.screenVertex.rightTop.x),
			static_cast<int>(ts->titleLogo.screenVertex.rightTop.y),
			static_cast<int>(ts->titleLogo.screenVertex.leftBottom.x),
			static_cast<int>(ts->titleLogo.screenVertex.leftBottom.y),
			static_cast<int>(ts->titleLogo.screenVertex.rightBottom.x),
			static_cast<int>(ts->titleLogo.screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, WHITE);
	}
	else
	{
		Novice::DrawQuad(
			static_cast<int>(ts->titleOne.screenVertex.leftTop.x),
			static_cast<int>(ts->titleOne.screenVertex.leftTop.y),
			static_cast<int>(ts->titleOne.screenVertex.rightTop.x),
			static_cast<int>(ts->titleOne.screenVertex.rightTop.y),
			static_cast<int>(ts->titleOne.screenVertex.leftBottom.x),
			static_cast<int>(ts->titleOne.screenVertex.leftBottom.y),
			static_cast<int>(ts->titleOne.screenVertex.rightBottom.x),
			static_cast<int>(ts->titleOne.screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ts->titleLogoColor);

		Novice::DrawQuad(
			static_cast<int>(ts->titleTwo.screenVertex.leftTop.x),
			static_cast<int>(ts->titleTwo.screenVertex.leftTop.y),
			static_cast<int>(ts->titleTwo.screenVertex.rightTop.x),
			static_cast<int>(ts->titleTwo.screenVertex.rightTop.y),
			static_cast<int>(ts->titleTwo.screenVertex.leftBottom.x),
			static_cast<int>(ts->titleTwo.screenVertex.leftBottom.y),
			static_cast<int>(ts->titleTwo.screenVertex.rightBottom.x),
			static_cast<int>(ts->titleTwo.screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ts->titleLogoColor);

		Novice::DrawQuad(
			static_cast<int>(ts->titleThree.screenVertex.leftTop.x),
			static_cast<int>(ts->titleThree.screenVertex.leftTop.y),
			static_cast<int>(ts->titleThree.screenVertex.rightTop.x),
			static_cast<int>(ts->titleThree.screenVertex.rightTop.y),
			static_cast<int>(ts->titleThree.screenVertex.leftBottom.x),
			static_cast<int>(ts->titleThree.screenVertex.leftBottom.y),
			static_cast<int>(ts->titleThree.screenVertex.rightBottom.x),
			static_cast<int>(ts->titleThree.screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ts->titleLogoColor);

		Novice::DrawQuad(
			static_cast<int>(ts->titleFour.screenVertex.leftTop.x),
			static_cast<int>(ts->titleFour.screenVertex.leftTop.y),
			static_cast<int>(ts->titleFour.screenVertex.rightTop.x),
			static_cast<int>(ts->titleFour.screenVertex.rightTop.y),
			static_cast<int>(ts->titleFour.screenVertex.leftBottom.x),
			static_cast<int>(ts->titleFour.screenVertex.leftBottom.y),
			static_cast<int>(ts->titleFour.screenVertex.rightBottom.x),
			static_cast<int>(ts->titleFour.screenVertex.rightBottom.y),
			0, 0, 0, 0, 0, ts->titleLogoColor);
	}
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ts->fadeColor, kFillModeSolid);

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ts->titleFadeColor, kFillModeSolid);


#if defined(_DEBUG)
	ScreenPrintfTitleScene();
#endif
}

//========================================================
// タイトルシーンの初期化
//========================================================

void InitTitleScene(TitleScene* ts)
{
	ts->fadeIn.isEase = true;
	ts->fadeIn.endColor = opaque;
	ts->fadeOut.startColor = transparent;
	ts->isNextScene = false;

	ts->fadeColor = transparent;
	ts->titleFadeOut.endColor = 0xFFFFFFFF;
	ts->titleFadeIn.startColor = 0xFFFFFFFF;

	ts->titleLogoFade.startColor = opaque;
	ts->titleLogoFade.endColor = 0xFFFFFFFF;
	ts->titleLogoFade.interval = 0.003f;

	ts->titleLogo.pos.x = 600;
	ts->titleLogo.pos.y = 450;
	ts->titleLogo.width = 400;
	ts->titleLogo.height = 100;

	ts->titleOne.pos.x = -100;
	ts->titleOne.pos.y = -100;
	ts->titleOne.width = 100;
	ts->titleOne.height = 100;
	ts->titleOneStart.x = 0.0f;
	ts->titleOneStart.y = 500.0f;
	ts->titleOneEnd.x = 450.0f;
	ts->titleOneEnd.y = 500.0f;

	ts->titleTwo.pos.x = -100;
	ts->titleTwo.pos.y = -100;
	ts->titleTwo.width = 101;
	ts->titleTwo.height = 100;
	ts->titleTwoStart.x = 550.0f;
	ts->titleTwoStart.y = 820.0f;
	ts->titleTwoEnd.x = 550.0f;
	ts->titleTwoEnd.y = 499.9f;

	ts->titleThree.pos.x = -100;
	ts->titleThree.pos.y = -100;
	ts->titleThree.width = 100;
	ts->titleThree.height = 100;
	ts->titleThreeStart.x = 650.0f;
	ts->titleThreeStart.y = 0.0f;
	ts->titleThreeEnd.x = 650.0f;
	ts->titleThreeEnd.y = 500.0f;

	ts->titleFour.pos.x = -100;
	ts->titleFour.pos.y = -100;
	ts->titleFour.width = 100;
	ts->titleFour.height = 100;
	ts->titleFourStart.x = 1280.0f;
	ts->titleFourStart.y = 500.0f;
	ts->titleFourEnd.x = 750.0f;
	ts->titleFourEnd.y = 500.0f;

	ts->amplitude = 10.0f;
	ts->theta = 0.0f;
}



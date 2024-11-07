#include "Structures.h"
#include "TitleScene.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Rectangle.h"



//========================================================
// タイトルシーンの更新処理
//========================================================

Scene UpdateTitleScene(TitleScene* ts, SelectScene* ss)
{

	Scene nextScene = Title;

	if (ts->fadeIn.isEase)
	{
		ColorLinearInterpolation(ts->fadeColor, transparent, ts->fadeColor, ts->fadeIn);
		CountEaseInOutTimer(ts->fadeIn);
	}
	else
	{

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
				ColorLinearInterpolation(ts->fadeColor, opaque, ts->fadeColor, ts->fadeOut);
				CountEaseInOutTimer(ts->fadeOut);
			}
			else
			{
				InitSelectScene(ss);

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

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ts->fadeColor, kFillModeSolid);

	Novice::DrawQuad(
		static_cast<int>(ts->titleLogo.screenVertex.leftTop.x),
		static_cast<int>(ts->titleLogo.screenVertex.leftTop.y),
		static_cast<int>(ts->titleLogo.screenVertex.rightTop.x),
		static_cast<int>(ts->titleLogo.screenVertex.rightTop.y),
		static_cast<int>(ts->titleLogo.screenVertex.lehtBottom.x),
		static_cast<int>(ts->titleLogo.screenVertex.lehtBottom.y),
		static_cast<int>(ts->titleLogo.screenVertex.rightBottom.x),
		static_cast<int>(ts->titleLogo.screenVertex.rightBottom.y),
		0, 0, 0, 0, 0, WHITE);


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
	ts->isNextScene = false;

	ts->titleLogo.pos.x = 450;
	ts->titleLogo.pos.y = 500;

	ts->titleLogo.width = 400;
	ts->titleLogo.height = 70;

	CalcVertexRectangle(&ts->titleLogo);
	ConvertWorldToScreenRectangle(&ts->titleLogo);
}



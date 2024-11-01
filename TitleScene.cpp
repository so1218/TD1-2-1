#include "Structures.h"
#include "TitleScene.h"
#include "Easing.h"
#include "SelectScene.h"


//========================================================
// タイトルシーンの更新処理
//========================================================

Scene UpdateTitleScene(TitleScene* ts)
{

	Scene nextScene = Title;

	//if (ts->fadeIn.isEase)
	//{
	//	ColorLinearInterpolation(BLACK, 0xffffff00, ts->current, ts->colorEase);
	//	CountEaseTimer(ts->colorEase);
	//}

	if (ts->gm->keys[DIK_SPACE] && !ts->gm->preKeys[DIK_SPACE])
	{
		InitSelectScene();
	
		nextScene = Select;
	}

	if (ts->gm->keys[DIK_G] && !ts->gm->preKeys[DIK_G])
	{
		ts->colorEase.isEase = true;
	}

	if (ts->colorEase.isEase)
	{
		ColorLinearInterpolation(BLACK, 0xffffff00, ts->current, ts->colorEase);
		CountEaseTimer(ts->colorEase);
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

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, ts->current, kFillModeSolid);

	Novice::DrawQuad(
		static_cast<int>(ts->titleLogo.sVertex.TL.x),
		static_cast<int>(kWindowHeight - ts->titleLogo.sVertex.TL.y),
		static_cast<int>(ts->titleLogo.sVertex.TR.x),
		static_cast<int>(kWindowHeight - ts->titleLogo.sVertex.TR.y),
		static_cast<int>(ts->titleLogo.sVertex.BL.x),
		static_cast<int>(kWindowHeight - ts->titleLogo.sVertex.BL.y),
		static_cast<int>(ts->titleLogo.sVertex.BR.x),
		static_cast<int>(kWindowHeight - ts->titleLogo.sVertex.BR.y),
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
	ts->colorEase.isEase = false;
	ts->fadeIn.isEase = true;

	ts->titleLogo.pos.x = 450;
	ts->titleLogo.pos.y = 500;

	ts->titleLogo.width = 400;
	ts->titleLogo.height = 70;

	ts->titleLogo.vertex.TL = { -ts->titleLogo.width / 2.0f, ts->titleLogo.height / 2.0f };
	ts->titleLogo.vertex.TR = { ts->titleLogo.width / 2.0f, ts->titleLogo.height / 2.0f };
	ts->titleLogo.vertex.BL = { -ts->titleLogo.width / 2.0f, -ts->titleLogo.height / 2.0f };
	ts->titleLogo.vertex.BR = { ts->titleLogo.width / 2.0f, -ts->titleLogo.height / 2.0f };
	
	ts->titleLogo.sVertex.TL = { ts->titleLogo.vertex.TL.x + ts->titleLogo.pos.x,ts->titleLogo.vertex.TL.y + ts->titleLogo.pos.y };
	ts->titleLogo.sVertex.TR = { ts->titleLogo.vertex.TR.x + ts->titleLogo.pos.x,ts->titleLogo.vertex.TR.y + ts->titleLogo.pos.y };
	ts->titleLogo.sVertex.BL = { ts->titleLogo.vertex.BL.x + ts->titleLogo.pos.x,ts->titleLogo.vertex.BL.y + ts->titleLogo.pos.y };
	ts->titleLogo.sVertex.BR = { ts->titleLogo.vertex.BR.x + ts->titleLogo.pos.x,ts->titleLogo.vertex.BR.y + ts->titleLogo.pos.y };
}



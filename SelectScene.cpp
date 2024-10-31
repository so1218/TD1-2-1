#include "Structures.h"
#include "Map.h"
#include "Player.h"

//========================================================
// セレクトシーンの更新処理
//========================================================

Scene UpdateSelectScene(SelectScene* ss, Map* map, Player* player)
{
	Scene nextScene = Select;

	if (ss->gm->keys[DIK_SPACE] && !ss->gm->preKeys[DIK_SPACE])
	{
		MapSetting(map);
		InitPlayer(player, map);
		Novice::SetJoystickDeadZone(0, 8000, 8000); // 左右スティックのデッドゾーンを設定
		nextScene = Play;
	}

	return nextScene;

}

//========================================================
// セレクトシーンの描画処理
//========================================================

// セレクトシーンのデバック(デバックモードのみ)
void ScreenPrintfSelectScene()
{
	Novice::ScreenPrintf(0, 0, "Select");
}

// セレクトシーンの描画
void DrawSelectScene()
{



#if defined(_DEBUG)
	ScreenPrintfSelectScene();
#endif
}

//========================================================
// セレクトシーンの初期化
//========================================================

void InitSelectScene() 
{

}
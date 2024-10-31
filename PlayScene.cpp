#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"

//========================================================
// プレイシーンの更新処理
//========================================================

Scene UpdatePlayScene(PlayScene* ps, Player* player, GameManager* gm)
{
	Scene nextScene = Play;

	MovePlayer(player, gm);

	if (ps->gm->keys[DIK_SPACE] && !ps->gm->preKeys[DIK_SPACE])
	{
		

		InitSelectScene();
		nextScene = Select;
	}

	
				
	return nextScene;

}

//========================================================
// プレイシーンの描画処理
//========================================================

// プレイシーンのデバック(デバックモードのみ)
void ScreenPrintfPlayScene()
{
	Novice::ScreenPrintf(0, 0, "Play");
}

// プレイシーンの描画
void DrawPlayScene(Map* map, Player* player) 
{
	DrawMap(map);
	DrawPlayer(player);
	
#if defined(_DEBUG)
	ScreenPrintfPlayScene();
#endif
}

//========================================================
// プレイシーンの初期化
//========================================================

void InitPlayScene()
{

}


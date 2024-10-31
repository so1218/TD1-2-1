#include "Structures.h"
#include "BezierCurve.h"
#include "Easing.h"
#include "map.h"
#include "Player.h"
#include "Particle.h"
#include "Rectangle.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "GrovalAudio.h"

const char kWindowTitle[] = "TD2";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

#if defined(_DEBUG)
	Scene currentScene = Title;
#else
	Scene currentScene = Select;
#endif



	int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);

	TitleScene ts;
	SelectScene ss;
	PlayScene ps;
	GameManager gm;
	Map map;
	Player player;
	Camera camera;
	Easing easing;

	InitTitleScene(&ts);
	AudioInitialize();

#if defined(_DEBUG)
	map.stageNo = 0;
#else
	map.stageNo = 1;
#endif

	//プレイシーンの中に必要な変数を格納
	ps.gm = &gm;

	//タイトルシーンの中に必要な変数を格納
	ts.gm = &gm;

	//セレクトシーンの中に必要な変数を格納
	ss.gm = &gm;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(gm.preKeys, gm.keys, 256);
		Novice::GetHitKeyStateAll(gm.keys);

		///
		/// ↓更新処理ここから
		///

		switch (currentScene)
		{
		case Title:

			currentScene = UpdateTitleScene(&ts);

			break;

		case Select:

			currentScene = UpdateSelectScene(&ss, &map, &player);

			break;

		case Play:

			currentScene = UpdatePlayScene(&ps, &player, &gm);

			break;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (currentScene)
		{
		case Title:

			DrawTitleScene(&ts);

			break;

		case Select:

			DrawSelectScene();

			break;

		case Play:

			DrawPlayScene(&map, &player);

			break;

		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

#pragma once

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <vector>

const int kWindowWidth = 900;
const int kWindowHeight = 700;

const int kPlayerParticleAmount = 16;
const int kBackParticleAmount = 32;
const int kParticleCountAroundPlayer = 32;
const unsigned int transparent = 0x00000000;
const unsigned int opaque = 0x000000FF;

//シーン
enum Scene
{
	Title = 0,
	Select = 1,
	Play = 2,
};

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;
};

struct IntVector2 
{
	int x = 0;
	int y = 0;
};

//3x3行列の構造体
struct Matrix3x3 
{
	float m[3][3];
};

// 物理的要素
struct PhysicalElements
{
	Vector2 velocity = {};
	Vector2 acceleration = {};
};

//イージングの構造体
struct Easing
{
	float interval = 0.01f;
	float cycle = 0.0f;
	float timer = 0.0f;
	float easeTimer = 0.0f;
	bool isEase = false;
};

// (T = Top, B = Bottom, L = Left, R = Right)
struct Vertex
{
	Vector2 TL;
	Vector2 TR;
	Vector2 BL;
	Vector2 BR;
};


// (T = Top, B = Bottom, L = Left, R = Right)
struct VertexOnMap
{
	IntVector2 TL;
	IntVector2 TR;
	IntVector2 BL;
	IntVector2 BR;
};

// 四角形の構造体
struct RectangleObject
{
	Vector2 pos;

	// 移動前の座標
	Vector2 prePos;

	// 移動後の座標
	Vector2 nextPos;

	// 4つの頂点の座標
	Vertex vertex;

	// スクリーン用の４つ角 (s = screen)
	Vertex sVertex;

	// 座標が移動する直前の4つ角の保管。当たり判定で使う。 (p = pre)
	Vertex pVertex;

	// 頂点バッファー (b = buffer)
	Vertex bVertex;

	// マップ単位の頂点座標
	VertexOnMap mVertex;
	float width = 0.0f;
	float height = 0.0f;
	Vector2 radius = { 0.0f, 0.0f };

};

//ゲームオブジェクトに関する構造体
struct GameObject :RectangleObject
{
	Vector2 pos;
	Vector2 eDir = { 1.0f, 0.0f };      //位置の単位ベクトル
	Vector2 scale = { 1.0f, 1.0f };
	bool isExist = true;
	unsigned int color = WHITE;
	float theta = 0.0f;                 //角度
	float speed = 0.0f;
	int GH = 0;                         //GraphicHandle。0で「White1x1」
	IntVector2 currentChipNo;          //現在いるチップのナンバー格納用。{y,x}。
	IntVector2 nextChipNo;				//次回いるチップのナンバー格納用。{y,x}。
	bool sidesCollision[3][3] = {};	    //周囲の８マスのマップチップとぶつかっているかどうか。

	Vector2 initialPos;
};


// マップチップに関する構造体
struct MapChip :GameObject
{
	int chipType = 0;                       //チップの種類

	Vector2 pos;

	float height = 50.0f;
	float width = 50.0f;

	unsigned int color = WHITE;

};

//カメラ関係の構造体
struct Camera
{
	Vector2 pos = { 0,960 };                //ワールド座標
	Vector2 scale{ 1.0f, -1.0f };
	//カメラの振れ幅
	static  const int hurehabaCopy = 50;
	int hurehaba = hurehabaCopy;
	//シェイクの信号
	bool isShake = false;

	//シェイク関係
	int shakeDuration = 20; 
	int shakeCounter = 0;
	int magnitude = 20;
	int randCameraX = 0;
	int randCameraY = 0;
};

struct GameManager
{
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int numJoysticks = Novice::GetNumberOfJoysticks();

	Camera camera;
	//画面外境界線。mainの画面サイズの書き換えも手打ち。マップチップのサイズ等で変動あり
	static constexpr float screenTop = 700;                                                    
	static constexpr float screenLeft = 0;                                                     
	static constexpr float screenRight = 900;                                                  
	static constexpr float screenBottom = 0;                                                   


};


struct StageImage :RectangleObject
{
	Vector2 screen;
	float scale;
	bool isSelect;
};

//ビットマップフォントの構造体
struct BitMapFont
{

	//そのステージの制限時間
	int timeLimit = 60 * 30;

	//制限時間のビットマップフォント
	int timeLimitArray[2];
	int timeLimitSurplus;

	//カラー
	unsigned int color = 0xFFFFFFFF;

	//そのステージがクリアしたかどうか
	bool haveStageCompleted = false;        //そのステージがクリア済みかどうかの変数

	StageImage scoreBitMap[5];
	StageImage maxScoreBitMap[5];
	StageImage timeLimitBitMap[2];
	StageImage score_Font;
	StageImage time_Font;

};

//カラーの遷移演出などに関する構造体
struct ChangingColor 
{

	unsigned int changingBackColor = BLACK;

};


//マップに関する構造体
struct Map
{
	static const int kFloorWidth = 18;		//マップチップの横個数
	static const int kFloorHeight = 14;	    //縦個数
	static const int stageSum = 10;          //ステージの総数
	int stageNo = 0;                        //ステージのナンバリング。セレクトシーンで変更。

	Easing easing;
	Vector2 pos;

	float easingTimer = 0.0f;


	enum ChipType
	{
		none = 0,
		block = 1,
	}chipType = none;

	int backType = 0;

	MapChip chip[kFloorHeight][kFloorWidth];

	Map()
	{
		//チップの座標と４つ角を設定
		for (int i = 0; i < kFloorHeight; ++i)
		{
			for (int j = 0; j < kFloorWidth; ++j)
			{
				chip[i][j].pos.x = float(chip[i][j].width / 2.0f + (j * chip[i][j].width));
				chip[i][j].pos.y = float(GameManager::screenTop - chip[i][j].height / 2.0f - (i * chip[i][j].height));
			}
		}
	}

	// 補完用の変数
	float targetPosX[kFloorHeight][kFloorWidth]; // ターゲットのX位置
	float targetPosY[kFloorHeight][kFloorWidth]; // ターゲットのY位置
	float moveSpeed = 0.0f; // 補完速度

};

//パーティクルの構造体
struct Particle :GameObject, PhysicalElements
{    
	Vector2 speed;     
	float lifetime;    
	float gravity;     
	bool isActive;     
	
	float radius;
	int direction;
	int emitterRange;
	
	int frameCount;

	
};

//プレイヤーの周りにあるパーティクル
struct ParticlAroundPlayer :Particle
{
	int color;         
	float size;        
	float fadeSpeed;   

};

//プレイヤーの構造体
struct Player :GameObject, PhysicalElements
{
	Particle particle[kPlayerParticleAmount];
	Easing easing;
	Vector2 scaleOnPtr[3];	

	//プレイヤーの向き
	enum Direction
	{
		up = 0,
		left = 1,
		down = 2,
		right = 3
	};

	//プレイヤーのパーティクル、挙動
	int direction = 0;
	bool isTrigger = false;
	int nextDirection = 0;
	int newDirection = 0;
	int intervalTimer = 60;
	int reflectTimer = 0;
	int rotateTimer = 0;
	int rotateInterval = 1;
	int stopTimer = 0;
	bool isStartDash = false;
	bool isReflect = false;
	bool isRotated = false;
	bool isStop = false;

};



//プレイシーンの構造体
struct PlayScene :GameObject
{

	Easing fadeIn;
	Easing fadeOut;
	unsigned int transparent = 0x00000000;
	unsigned int opaque = 0x000000FF;
	unsigned int current = 0x00000000;

	bool isNextScene = false;

	Easing playerAppear;

	//クリア画面
	RectangleObject clearScreen;
	bool isStageCleared = false;
	int clearGH = 0;

	const int kMaxTimer = 180;
	int timer = 0;

	bool isStart = false;

	//スポーン演出が終わったかどうか
	bool spawned = false;
	//死亡演出
	bool deadPerform = false;
	bool initialized = false;		//false であれば初期化する

	Player player;

	GameManager* gm;
	Map* map;

	//これがトゥルーになったら、ステージセレクトへ遷移
	bool reachGoal = false;
	bool stageCleared = false;

	bool isNextSelect = false;
};

//タイトルシーンの構造体
struct TitleScene
{
	GameManager* gm;
	
	GameObject titleLogo;
};

//セレクトシーンの構造体
struct SelectScene
{
	GameManager* gm;

};
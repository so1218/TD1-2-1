#pragma once

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <vector>

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

const int kAmount50 = 50;
const int kAmount100 = 100;
const int kAmount200 = 200;

//透明色
const unsigned int transparent = 0x00000000;
//有色(黒)
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
	Vector2 leftTop;
	Vector2 lehtBottom;
	Vector2 rightTop;
	Vector2 rightBottom;
};


// (T = Top, B = Bottom, L = Left, R = Right)
struct VertexOnMap
{
	IntVector2 leftTop;
	IntVector2 leftBottom;
	IntVector2 rightTop;
	IntVector2 rightBottom;
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

	// スクリーン用の４つ角 
	Vertex screenVertex;

	// 座標が移動する直前の4つ角の保管。当たり判定で使う。
	Vertex preVertex;

	// 頂点バッファー
	Vertex bufferVertex;

	// マップ単位の頂点座標
	VertexOnMap mapVertex;
	float width = 0.0f;
	float height = 0.0f;
	Vector2 radius = { 0.0f, 0.0f };

};

struct Circle
{
	Vector2 center;    
	Vector2 radius = { 0.0f, 0.0f };
};

//ゲームオブジェクトに関する構造体
struct GameObject :RectangleObject, PhysicalElements
{
	Vector2 eDir = { 1.0f, 0.0f };      //位置の単位ベクトル
	Vector2 scale = { 1.0f, 1.0f };
	bool isExist = true;
	unsigned int color = WHITE;
	float theta = 0.0f;                 //角度
	float angle;
	float speed = 0.0f;
	Vector2 directionVec = {};
	Vector2 normalizedDirection = {};
	int GH = 0;                         //GraphicHandle。0で「White1x1」
	IntVector2 currentChipNo;          //現在いるチップのナンバー格納用。{y,x}。
	IntVector2 nextChipNo;				//次回いるチップのナンバー格納用。{y,x}。
	IntVector2 startChipNo;
	bool sidesCollision[3][3] = {};	    //周囲の８マスのマップチップとぶつかっているかどうか。
	bool isNextScene = false;

	int frameCount = 0;

	Vector2 initialPos;
};


// マップチップに関する構造体
struct MapChip :GameObject
{
	int chipType = 0;                       //チップの種類

	Vector2 pos;

	float height = 64.0f;
	float width = 64.0f;

	unsigned int color = WHITE;

};

struct BlendModeFunc
{
	int mode = 1;
	int choiceType = 1;

	enum BlendModeType
	{
		None = 0,
		Normal = 1,
		Add = 2,
		Subtract = 3,
		Multiply = 4,
		Screen = 5,
		Exclusion = 6
	};
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
	static const int kFloorWidth = 20;		//マップチップの横個数
	static const int kFloorHeight = 10;	    //縦個数
	static const int stageSum = 4;          //ステージの総数
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
struct Particle :GameObject
{    
	float lifetime;
	int direction;
	int radius = 10;
	IntVector2 emitterRange = { 80,80 };
	IntVector2 activeDistance = { 60,60 };
	Vector2 speed = {};
	float gravity = 0.7f;
	int appearInterval = 20;
	
	BlendModeFunc blendMode;

	Easing easingInOut;
	Easing easingOut;
	Easing easingIn;

	int amount;
};

//プレイヤーの構造体
struct Player :GameObject
{
	Easing easing;
	Vector2 scaleOnPtr[3];	
	Particle aroundParticle[kAmount50];
	Particle toCenterParticle[kAmount50];

	//プレイヤーの向き
	enum Direction
	{
		up = 0,
		left = 1,
		down = 2,
		right = 3
	};

};


struct Bullet: GameObject
{

	int amount = 16;
	int directionCount = 16;
	float angleStep;

	bool isAction = false;
	bool hasAction = false;

	int appearInterval = 20;

};

struct BossType1 :GameObject
{
	Easing MoveEase;
	Particle aroundParticle[kAmount50];
	Particle goUpParticle[kAmount50];
	Particle impactDustParticle[kAmount50];

	Bullet bulletSomeway[kAmount50];
	Bullet bulletToPlayer[kAmount50];

	float toPlayerDir;

	Vector2 knockbackDir;
	Vector2 knockbackNormalizedDir;
	float knockbackStrength = 10;
	PhysicalElements knockback;
	Easing knockbackEase;
	bool isKnockback = false;

	bool isAction = false;
	int actionFrameCounter = 0;
	int randAction = 0;

};

struct BossType2 :GameObject
{
	Easing MoveEase;
	float toPlayerDistance;
};

struct Boss
{
	BossType1 T1;
};

//プレイシーンの構造体
struct PlayScene :GameObject
{

	Easing fadeIn;
	Easing fadeOut;
	unsigned int fadeColor = 0x000000ff;

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

	GameObject playerHpIcon[3];

};

//タイトルシーンの構造体
struct TitleScene: GameObject
{

	GameManager* gm;
	Easing fadeIn;
	Easing fadeOut;
	unsigned int fadeColor = 0x000000ff;

	Easing colorEase;
	
	GameObject titleLogo;

};

//セレクトシーンの構造体
struct SelectScene: GameObject
{
	GameManager* gm;

	Easing fadeIn;
	Easing fadeOut;
	unsigned int fadeColor = 0x000000ff;

	Vector2 tutorialPos = { 590.0f,520.0f };
	float tutorialWidth = 100.0f;
	float tutorialHeight = 100.0f;
	Vector2 stageOnePos = { 190.0f,320.0f };
	float stageOneWidth = 100.0f;
	float stageOneHeight = 100.0f;
	Vector2 stageTwoPos = { 590.0f,120.0f };
	float stageTwoWidth = 100.0f;
	float stageTwoHeight = 100.0f;
	Vector2 stageThreePos = { 990.0f,320.0f };
	float stageThreeWidth = 100.0f;
	float stageThreeHeight = 100.0f;


};
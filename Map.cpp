﻿#include "Structures.h"

//========================================================
// マップの設定、初期化
//========================================================

void MapSetting(Map* map)
{
	//マップチップの配置
	int static chipData[map->stageSum][map->kFloorHeight][map->kFloorWidth]
	{
		//ステージ0
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		},

		//ステージ1
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		},

		//ステージ2
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		},

		//ステージ3
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		},

		

	};

	if (map->stageNo == 0)
	{
		
	}

	else if (map->stageNo == 1)
	{
		
	}

	else if (map->stageNo == 2)
	{
		
	}

	else if (map->stageNo == 3)
	{
		
	}

	else if (map->stageNo == 4)
	{
		
	}

	else if (map->stageNo == 5)
	{
		
	}

	else if (map->stageNo == 6)
	{
		
	}

	else if (map->stageNo == 7)
	{
		
	}

	else if (map->stageNo == 8)
	{
		
	}

	else if (map->stageNo == 9)
	{
		
	}

	
	//チップデータを設定
	for (int k = map->stageNo; k < map->stageNo + 1; ++k)
	{
		
		for (int i = 0; i < map->kFloorHeight; ++i)
		{
			for (int j = 0; j < map->kFloorWidth; ++j)
			{

				map->chip[i][j].chipType = chipData[k][i][j];

				switch (map->chip[i][j].chipType) {

					case map->none:

						map->chip[i][j].color = 0x00000000;

						break;			

					case map->block:

						map->chip[i][j].color = BLACK;

						break;


					default:

						break;
					
				}
			}
		}
	}
}

//========================================================
// マップの描画
//========================================================

void DrawMap(Map* map)
{


	for (int i = 0; i < map->kFloorHeight; ++i)
	{
		for (int j = 0; j < map->kFloorWidth; ++j)
		{
		
			Novice::DrawQuad(
				static_cast<int>(map->chip[i][j].pos.x - map->chip[i][j].width / 2),
				static_cast<int>(kWindowHeight - (map->chip[i][j].pos.y - map->chip[i][j].height / 2)),
				static_cast<int>(map->chip[i][j].pos.x + map->chip[i][j].width / 2),
				static_cast<int>(kWindowHeight - (map->chip[i][j].pos.y - map->chip[i][j].height / 2)),
				static_cast<int>(map->chip[i][j].pos.x - map->chip[i][j].width / 2),
				static_cast<int>(kWindowHeight - (map->chip[i][j].pos.y + map->chip[i][j].height / 2)),
				static_cast<int>(map->chip[i][j].pos.x + map->chip[i][j].width / 2),
				static_cast<int>(kWindowHeight - (map->chip[i][j].pos.y + map->chip[i][j].height / 2)),
				0, 0, 0, 0, 0, map->chip[i][j].color);
			
		}
	}

	// マス目の線
	for (int i = 0; i < map->kFloorHeight; ++i) 
	{
		
		Novice::DrawLine(0, static_cast<int>(i * map->chip[0][0].height), kWindowWidth, static_cast<int>(i * map->chip[0][0].height), WHITE);
		
	}

	for (int i = 0; i < map->kFloorWidth; ++i) 
	{
		
		Novice::DrawLine(static_cast<int>(i * map->chip[0][0].width), 0, static_cast<int>(i * map->chip[0][0].width), kWindowHeight, WHITE);
		
	}
}
#pragma once

#define DEBUG

#define FPS				60										//FPS

#define SCREEN_WIDTH	1280									//スクリーンの横幅
#define SCREEN_HEIGHT	720										//スクリーンの縦幅

#define BLOCK_WIDTH     50										//1ブロックの横幅
#define BLOCK_HEIGHT    50										//1ブロックの縦幅

#define WORLD_BLOCK_X   100										//X座標配置するブロック数
#define WORLD_BLOCK_Y   28										//Y座標配置するブロック数

#define WORLD_WIDTH		BLOCK_WIDTH * WORLD_BLOCK_X				//ワールドの横幅
#define WORLD_HEIGHT	BLOCK_HEIGHT * WORLD_BLOCK_Y			//ワールドの縦幅

#define GROUND_LINE		WORLD_HEIGHT - 100						//地面

#define DEGREE_TO_RADIAN(_deg)	_deg * (DX_PI_F / 180.f)		//角度からラジアンへ
#define RADIAN_TO_DEGREE(_rad)	_rad * (180.f / DX_PI_F)		//ラジアンから角度へ

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"

#include"../InputControl/Key/KeyInput.h"
#include"../InputControl/Pad/PadInput.h"

#include<map>			//連想配列
#include<string>		//文字列
#include<sstream>		//文字ストリーム
#include<fstream>		//ファイルストリーム
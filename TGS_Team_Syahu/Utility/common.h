#pragma once

#define FPS				60									//FPS

#define SCREEN_WIDTH	1280								//スクリーンの横幅
#define SCREEN_HEIGHT	720									//スクリーンの縦幅

#define WORLD_WIDTH		2560								//ワールドの横幅
#define WORLD_HEIGHT	1440								//ワールドの縦幅

#define GROUND_LINE		WORLD_HEIGHT - 100	//地面

#define DEGREE_TO_RADIAN(_deg)	_deg * (DX_PI_F / 180)		//角度からラジアンへ
#define RADIAN_TO_DEGREE(_rad)	_rad * (180 / DX_PI_F)		//ラジアンから角度へ

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"

#include"../InputControl/Key/KeyInput.h"
#include"../InputControl/Pad/PadInput.h"

#include<map>			//連想配列
#include<string>		//文字列
#include<sstream>		//文字ストリーム
#include<fstream>		//ファイルストリーム
#pragma once

#define FPS				60					//FPS

#define SCREEN_WIDTH	1280				//スクリーンの横幅
#define SCREEN_HEIGHT	720					//スクリーンの縦幅

#define WORLD_WIDTH		2560				//ワールドの横幅
#define WORLD_HEIGHT	1440				//ワールドの縦幅

#define GROUND_LINE		630 * 2				//地面
#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"

#include"../InputControl/Key/KeyInput.h"
#include"../InputControl/Pad/PadInput.h"

#include<map>			//連想配列
#include<string>		//文字列
#include<sstream>		//文字ストリーム
#include<fstream>		//ファイルストリーム
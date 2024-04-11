#pragma once

#define FPS				60					//FPS

#define SCREEN_WIDTH	1280				//画面の横幅
#define SCREEN_HEIGHT	720					//画面の縦幅

#define WORLD_WIDTH		2560				//世界の横幅
#define WORLD_HEIGHT	1440				//世界の縦幅

#define GROUND_LINE		630 * 2				//地面

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"

#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"

#include<map>			//連想配列
#include<string>		//文字列操作
#include<sstream>		//文字列変換
#include<fstream>		//ファイル操作
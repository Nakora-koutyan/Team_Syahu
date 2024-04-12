#pragma once
#include<DxLib.h>

#define MAX_KEY 256
#define MOUSE_OFFSET_X SCREEN_WIDTH	/ 2
#define MOUSE_OFFSET_Y SCREEN_HEIGHT / 2

struct MOUSE_INPUT
{
	int button;
	int x;
	int y;
};

class KeyInput
{
private:
	static char now_key[MAX_KEY];
	static char old_key[MAX_KEY];
	static MOUSE_INPUT now_mouse;
	static MOUSE_INPUT old_mouse;
	static MOUSE_INPUT mouse_vec;
	static float mouse_sensitivity;
public:
	//更新
	static void Update();

	//押したキーを取得
	static bool GetKey(int key);

	//押しているキーを取得
	static bool GetKeyDown(int key);

	//離したキーを取得
	static bool GetKeyUp(int key);

	//マウスのx座標を取得
	static int GetMouseLocationX();

	//マウスのy座標を取得
	static int GetMouseLocationY();

	//マウスの移動量xを取得
	static int GetMouseVecX();

	//マウスの移動量yを取得
	static int GetMouseVecY();
	
	//押したボタンを取得
	static bool GetButton(int key);

	//押しているボタンを取得
	static bool GetButtonDown(int key);

	//離したボタンを取得
	static bool GetButtonUp(int key);
};

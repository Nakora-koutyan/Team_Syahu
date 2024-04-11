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
	//更新処理
	static void Update();

	//キーを押したときを取得する
	static bool GetKey(int key);

	//キーを押しているとき取得する
	static bool GetKeyDown(int key);

	//キーを離したときを取得する
	static bool GetKeyUp(int key);

	//マウスのx座標を取得する
	static int GetMouseLocationX();

	//マウスのy座標を取得する
	static int GetMouseLocationY();

	//マウスの移動量xを取得する
	static int GetMouseVecX();

	//マウスの移動量yを取得する
	static int GetMouseVecY();
	
	//ボタンを押したときを取得する
	static bool GetButton(int key);

	//ボタンを押しているときを取得する
	static bool GetButtonDown(int key);

	//ボタンを離したときを取得する
	static bool GetButtonUp(int key);
};




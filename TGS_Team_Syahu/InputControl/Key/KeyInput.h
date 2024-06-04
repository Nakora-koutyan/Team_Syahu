#pragma once
#include<DxLib.h>

#define MAX_KEY 256
#define MOUSE_OFFSET_X SCREEN_WIDTH	/ 2
#define MOUSE_OFFSET_Y SCREEN_HEIGHT / 2

struct MOUSE_INPUT
{
	int button;
	int wheel;
	int x;
	int y;
};

class KeyInput
{
private:
	static char nowKey[MAX_KEY];
	static char oldKey[MAX_KEY];
	static MOUSE_INPUT nowMouse;
	static MOUSE_INPUT oldMouse;
	static MOUSE_INPUT mouseVec;
	static MOUSE_INPUT mouseWheel;
	static float mouseSensitivity;
	static bool isShowMouse;
public:
	//更新
	static void Update();

public:
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

	//ホイールの回転量の取得
	static int GetMouseWheel();
	
	//押したボタンを取得
	static bool GetButton(int key);

	//押しているボタンを取得
	static bool GetButtonDown(int key);

	//離したボタンを取得
	static bool GetButtonUp(int key);

	//マウスの表示フラグの設定
	static void SetIsShowMouse(const bool flg) 
	{
		isShowMouse = flg; 
		flg ? SetMouseDispFlag(TRUE) : SetMouseDispFlag(FALSE);
	}
};

#pragma once
#include<DxLib.h>

#define MAX_KEY			256							//キーの数
#define MOUSE_OFFSET_X	SCREEN_WIDTH	/	2		//スクリーンの中心X
#define MOUSE_OFFSET_Y	SCREEN_HEIGHT	/	2		//スクリーンの中心Y

struct MOUSE_INPUT
{
	int button;		//ボタン
	int wheel;		//マウスホイール
	int x;			//座標X
	int y;			//座標Y
};

class KeyInput
{
private:
	static char nowKey[MAX_KEY];		//現在のキー
	static char oldKey[MAX_KEY];		//過去のキー
	static MOUSE_INPUT nowMouse;		//現在のマウス
	static MOUSE_INPUT oldMouse;		//過去のマウス
	static MOUSE_INPUT mouseVec;		//マウスのベクトル
	static float mouseSensitivity;		//マウスの感度
	static bool isShowMouse;			//マウスを表示する？
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

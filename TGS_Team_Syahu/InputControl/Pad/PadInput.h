#pragma once
#include"DxLib.h"

#define BUTTON		16				//ボタンの数
#define STICK_MAX	32767.f			//スティックの最大値
#define QUARTER		32767*0.25		//スティックの1/4

struct Stick
{
	short x;	//スティックのx
	short y;	//スティックのy
};

class PadInput
{
private:
	static char nowKey[BUTTON];		//更新前のキー
	static char oldKey[BUTTON];		//更新後のキー
	static XINPUT_STATE input;		//入力
	static Stick lStick;			//左スティック
	static Stick rStick;			//右スティック
private:
	PadInput() = default;
public:
	//更新
	static void Update()
	{
		//コントローラーの取得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input);

		for (int i = 0; i < BUTTON; i++)
		{
			oldKey[i] = nowKey[i];
			nowKey[i] = input.Buttons[i];
		}

		//左スティック
		lStick.x = input.ThumbLX;
		lStick.y = input.ThumbLY;

		//右スティック
		rStick.x = input.ThumbRX;
		rStick.y = input.ThumbRY;
	}

	//押したボタンを取得
	static bool OnButton(int button)
	{
		bool ret = (nowKey[button] == TRUE && oldKey[button] == FALSE);
		return ret;
	}

	//押しているボタンを取得
	static bool OnPressed(int button)
	{
		bool ret = (nowKey[button] == TRUE);
		return ret;
	}

	//離したボタンを取得
	static bool OnRelease(int button)
	{
		bool ret = (nowKey[button] == FALSE && oldKey[button] == TRUE);
		return ret;
	}

	//右スティックの取得
	static Stick GetRStick()
	{
		return rStick;
	}

	//左スティックの取得
	static Stick GetLStick()
	{
		return lStick;
	}

	//右スティックのx座標を取得
	static float GetRStickRationX()
	{
		return rStick.x / STICK_MAX;
	}

	//右スティックのy座標を取得
	static float GetRStickRationY()
	{
		return rStick.y / STICK_MAX;
	}

	//左スティックのx座標を取得
	static float GetLStickRationX()
	{
		return lStick.x / STICK_MAX;
	}

	//左スティックのy座標を取得
	static float GetLStickRationY()
	{
		return lStick.y / STICK_MAX;
	}

};

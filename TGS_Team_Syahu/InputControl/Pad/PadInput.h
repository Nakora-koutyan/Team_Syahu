#pragma once
#include"DxLib.h"

#define BUTTON 16				//ボタンの数
#define STICK_MAX 32767.f		//スティックの最大値
#define QUARTER 32767*0.25		//スティックの1/4

struct Stick
{
	short x;	//スティックのx
	short y;	//スティックのy
};

class PadInput
{
private:
	static char now_key[BUTTON];	//更新前のキー
	static char old_key[BUTTON];	//更新後のキー
	static XINPUT_STATE input;		//入力
	static Stick l_stick;			//左スティック
	static Stick r_stick;			//右スティック
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
			old_key[i] = now_key[i];
			now_key[i] = input.Buttons[i];
		}

		//左スティック
		l_stick.x = input.ThumbLX;
		l_stick.y = input.ThumbLY;

		//右スティック
		r_stick.x = input.ThumbRX;
		r_stick.y = input.ThumbRY;
	}

	//押したボタンを取得
	static bool OnButton(int button)
	{
		bool ret = (now_key[button] == TRUE && old_key[button] == FALSE);
		return ret;
	}

	//押しているボタンを取得
	static bool OnPressed(int button)
	{
		bool ret = (now_key[button] == TRUE);
		return ret;
	}

	//離したボタンを取得
	static bool OnRelease(int button)
	{
		bool ret = (now_key[button] == FALSE && old_key[button] == TRUE);
		return ret;
	}

	//右スティックの取得
	static Stick GetRStick()
	{
		return r_stick;
	}

	//左スティックの取得
	static Stick GetLStick()
	{
		return l_stick;
	}

	//右スティックのx座標を取得
	static float GetRStickRationX()
	{
		return r_stick.x / STICK_MAX;
	}

	//右スティックのy座標を取得
	static float GetRStickRationY()
	{
		return r_stick.y / STICK_MAX;
	}

	//左スティックのx座標を取得
	static float GetLStickRationX()
	{
		return l_stick.x / STICK_MAX;
	}

	//左スティックのy座標を取得
	static float GetLStickRationY()
	{
		return l_stick.y / STICK_MAX;
	}

};

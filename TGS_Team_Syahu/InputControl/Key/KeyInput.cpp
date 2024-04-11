#include"../../Utility/common.h"

//静的メンバ変数の定義
char KeyInput::now_key[MAX_KEY];
char KeyInput::old_key[MAX_KEY];
MOUSE_INPUT KeyInput::now_mouse;
MOUSE_INPUT KeyInput::old_mouse;
MOUSE_INPUT KeyInput::mouse_vec;
float KeyInput::mouse_sensitivity = 1.f;

void KeyInput::Update()
{
	for (int i = 0; i < MAX_KEY; i++) 
	{
		old_key[i] = now_key[i];
	}

	old_mouse = now_mouse;
	//現在のマウス
	now_mouse.button = GetMouseInput();
	GetMousePoint(&now_mouse.x, &now_mouse.y);
	mouse_vec.x = (int)((now_mouse.x - MOUSE_OFFSET_X) * mouse_sensitivity);
	mouse_vec.y = (int)((now_mouse.y - MOUSE_OFFSET_Y) * mouse_sensitivity);

	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//現在のキー
	GetHitKeyStateAll(now_key);

}

bool KeyInput::GetKey(int key)
{
	bool ret = (now_key[key] == TRUE) && (old_key[key] != TRUE);

	return ret;
}

bool KeyInput::GetKeyDown(int key)
{
	bool ret = (now_key[key] == TRUE) && (old_key[key] == TRUE);

	return ret;
}

bool KeyInput::GetKeyUp(int key)
{
	bool ret = (now_key[key] != TRUE) && (old_key[key] == TRUE);

	return ret;
}

int KeyInput::GetMouseLocationX()
{
	int ret = now_mouse.x;

	return ret;
}

int KeyInput::GetMouseLocationY()
{
	int ret = now_mouse.y;

	return ret;
}

int KeyInput::GetMouseVecX()
{
	int ret = mouse_vec.x;

	return ret;
}

int KeyInput::GetMouseVecY()
{
	int ret = mouse_vec.y;

	return ret;
}

bool KeyInput::GetButton(int key)
{
	bool ret = ~(old_mouse.button & key) & (now_mouse.button & key);

	return ret;
}

bool KeyInput::GetButtonDown(int key)
{
	bool ret = (old_mouse.button & key) & (now_mouse.button & key);

	return ret;
}

bool KeyInput::GetButtonUp(int key)
{
	bool ret = (old_mouse.button & key) & ~(now_mouse.button & key);

	return ret;
}
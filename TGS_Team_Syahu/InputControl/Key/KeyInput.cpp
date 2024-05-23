#include"../../Utility/common.h"

//実体化
char KeyInput::nowKey[MAX_KEY];
char KeyInput::oldKey[MAX_KEY];
MOUSE_INPUT KeyInput::nowMouse;
MOUSE_INPUT KeyInput::oldMouse;
MOUSE_INPUT KeyInput::mouseVec;
float KeyInput::mouseSensitivity = 1.f;
bool KeyInput::isShowMouse = false;

void KeyInput::Update()
{
	for (int i = 0; i < MAX_KEY; i++) 
	{
		oldKey[i] = nowKey[i];
	}

	oldMouse = nowMouse;
	//マウスの更新
	nowMouse.button = GetMouseInput();
	GetMousePoint(&nowMouse.x, &nowMouse.y);
	mouseVec.x = (int)((nowMouse.x - MOUSE_OFFSET_X) * mouseSensitivity);
	mouseVec.y = (int)((nowMouse.y - MOUSE_OFFSET_Y) * mouseSensitivity);

	if (!isShowMouse)
	{
		SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	//キーの取得
	GetHitKeyStateAll(nowKey);

}

bool KeyInput::GetKey(int key)
{
	bool ret = (nowKey[key] == TRUE) && (oldKey[key] != TRUE);

	return ret;
}

bool KeyInput::GetKeyDown(int key)
{
	bool ret = (nowKey[key] == TRUE) && (oldKey[key] == TRUE);

	return ret;
}

bool KeyInput::GetKeyUp(int key)
{
	bool ret = (nowKey[key] != TRUE) && (oldKey[key] == TRUE);

	return ret;
}

int KeyInput::GetMouseLocationX()
{
	int ret = nowMouse.x;

	return ret;
}

int KeyInput::GetMouseLocationY()
{
	int ret = nowMouse.y;

	return ret;
}

int KeyInput::GetMouseVecX()
{
	int ret = mouseVec.x;

	return ret;
}

int KeyInput::GetMouseVecY()
{
	int ret = mouseVec.y;

	return ret;
}

bool KeyInput::GetButton(int key)
{
	bool ret = ~(oldMouse.button & key) & (nowMouse.button & key);

	return ret;
}

bool KeyInput::GetButtonDown(int key)
{
	bool ret = (oldMouse.button & key) & (nowMouse.button & key);

	return ret;
}

bool KeyInput::GetButtonUp(int key)
{
	bool ret = (oldMouse.button & key) & ~(nowMouse.button & key);

	return ret;
}
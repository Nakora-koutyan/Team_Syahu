#include"TitleScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../GameMain/GameMainScene.h"
#include"../End/EndScene.h"
#include"../Help/HelpScene.h"
#include"../../Utility/common.h"

TitleScene::TitleScene()
{
	cursorLocation.x = 0.f;
	cursorLocation.y = 0.f;

	intervalCursorCount = 0;
	cursorNum = 0;

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{

}

void TitleScene::Finalize()
{

}

SceneBase* TitleScene::Update()
{
	ResourceManager::PlayBGM("title");

	cursorLocation.y = (float)cursorNum * 100;

	if (intervalCursorCount < CURSOR_INTERVAL)
	{
		intervalCursorCount++;
	}

	//上
	if ((KeyInput::GetKeyDown(KEY_INPUT_W) || KeyInput::GetKeyDown(KEY_INPUT_UP) ||
		PadInput::GetLStickRationY() > 0.2 || PadInput::OnPressed(XINPUT_BUTTON_DPAD_UP)) &&
		intervalCursorCount >= CURSOR_INTERVAL)
	{
		ResourceManager::PlaySE("cursorMove", FALSE);

		cursorNum--;
		intervalCursorCount = 0;

		if (cursorNum < 0)
		{
			cursorNum = 2;
		}
	}
	//下
	else 
	if ((KeyInput::GetKeyDown(KEY_INPUT_S) || KeyInput::GetKeyDown(KEY_INPUT_DOWN) ||
		PadInput::GetLStickRationY() < -0.2 || PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN)) &&
		intervalCursorCount >= CURSOR_INTERVAL)
	{
		ResourceManager::PlaySE("cursorMove", FALSE);

		cursorNum++;
		intervalCursorCount = 0;

		if (cursorNum > 2)
		{
			cursorNum = 0;
		}
	}

	if (PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::GetKey(KEY_INPUT_SPACE))
	{
		ResourceManager::PlaySE("cursorSelect");

		if (cursorNum == 0)
		{
			return new GameMainScene();
		}
		else if (cursorNum == 1)
		{
			return new HelpScene();
		}
		else if (cursorNum == 2)
		{
			return new EndScene();
		}
	}

	return this;
}

void TitleScene::Draw() const
{
	DrawGraph(0, 0, ResourceManager::GetImage("Stage/Background/layer_1"), TRUE);
	DrawGraph(0, 198, ResourceManager::GetImage("Stage/Background/layer_2"), TRUE);
	DrawGraph(340, 60, ResourceManager::GetImage("Title/TitleText"), TRUE);

	DrawRotaGraphF(470, 360 + cursorLocation.y, 1, DEGREE_TO_RADIAN(90.f), ResourceManager::GetImage("UI/cursor"), TRUE);

	DrawGraph(530, (300 + 28), ResourceManager::GetImage("Title/StartText"), TRUE);
	DrawGraph(525, (300 + 15) + 100, ResourceManager::GetImage("Title/HelpText"), TRUE);
	DrawGraph(520, (300 + 26) + 200, ResourceManager::GetImage("Title/EndText"), TRUE);
}

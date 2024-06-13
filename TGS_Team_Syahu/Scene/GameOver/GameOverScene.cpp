#include"GameOverScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Scene/Title/TitleScene.h"
#include"../../Scene/GameMain/GameMainScene.h"
#include"../Utility/common.h"

GameOverScene::GameOverScene()
{
	cursorLocation.x = 0.f;
	cursorLocation.y = 0.f;

	intervaSceneCount = 0;
	intervalCursorCount = 0;
	cursorNum = 0;
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Initialize()
{

}

void GameOverScene::Finalize()
{

}

SceneBase* GameOverScene::Update()
{
	ResourceManager::PlayBGM("gameover");

	cursorLocation.y = (float)cursorNum * 100;

	if (intervalCursorCount < CURSOR_INTERVAL)
	{
		//カーソルのインターバル加算
		intervalCursorCount++;
	}

	if (intervaSceneCount < SCENE_INTERVAL)
	{	
		//シーンのインターバル加算
		intervaSceneCount++;
	}
	else
	{
		if ((KeyInput::GetKey(KEY_INPUT_SPACE) || PadInput::OnButton(XINPUT_BUTTON_A)))
		{
			ResourceManager::PlaySE("cursorSelect");

			if (cursorNum == 0)
			{
				return new GameMainScene();
			}
			else if (cursorNum == 1)
			{
				return new TitleScene();
			}
		}
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
			cursorNum = 1;
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

			if (cursorNum > 1)
			{
				cursorNum = 0;
			}
		}

	return this;
}

void GameOverScene::Draw() const
{
	//背景
	DrawGraph(0, 0, ResourceManager::GetImage("GameOver/GameOverBackGround"), TRUE);
	//ゲームオーバー
	DrawGraph(340, 130, ResourceManager::GetImage("GameOver/GameOverText"), TRUE);
	//コンティニュー
	DrawGraph(490, 340, ResourceManager::GetImage("GameOver/ContinueText"), TRUE);
	//タイトルへ戻る
	DrawGraph(475, 440, ResourceManager::GetImage("GameOver/BackTitleText"), TRUE);
	//カーソル
	DrawRotaGraphF(420, 390 + cursorLocation.y, 1, DEGREE_TO_RADIAN(90.f), ResourceManager::GetImage("UI/cursor"), TRUE);
}

#include "GameClearScene.h"
#include"../InputControl/Key/KeyInput.h"
#include"../InputControl/Pad/PadInput.h"
#include"../ResourceManager/ResourceManager.h"
#include"../Scene/Title/TitleScene.h"

GameClearScene::GameClearScene()
{
	intervalCount = 0;
	animCoun = 0;
	playerIdle = 0;
}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Initialize()
{

}

void GameClearScene::Finalize()
{

}

SceneBase* GameClearScene::Update()
{
	ResourceManager::PlayBGM("gameclear");

	animCoun++;

	if (animCoun % 14 == 0)
	{
		playerIdle++;
		if (playerIdle >= 2)
		{
			playerIdle = 0;
		}
	}

	if (intervalCount < SCENE_INTERVAL)
	{
		intervalCount++;
	}
	else
	{
		if ((KeyInput::GetKey(KEY_INPUT_SPACE) || PadInput::OnButton(XINPUT_BUTTON_A)))
		{
			return new TitleScene();
		}
	}

	return this;
}

void GameClearScene::Draw() const
{
	SetFontSize(64);
	DrawString(500, 200, "GameClear", 0xffffff);
	SetFontSize(16);

	DrawRotaGraph(650, 600, 1, 0, ResourceManager::GetDivImage("Player/player", playerIdle), TRUE);

}

#include"GameOverScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Scene/Title/TitleScene.h"

GameOverScene::GameOverScene()
{
	intervalCount = 0;
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

void GameOverScene::Draw() const
{
	SetFontSize(64);
	DrawString(500, 200, "GameOver", 0xffffff);
	SetFontSize(16);

	DrawRotaGraph(650, 600, 1, 0, ResourceManager::GetDivImage("Player/player", 63), TRUE);
}

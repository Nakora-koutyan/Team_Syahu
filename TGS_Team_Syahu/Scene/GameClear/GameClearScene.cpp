#include "GameClearScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Scene/Title/TitleScene.h"
#include"../../Utility/common.h"

GameClearScene::GameClearScene()
{
	intervaSceneCount = 0;
	animCount = 0;
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

	animCount++;

	if (animCount % 14 == 0)
	{
		playerIdle++;
		if (playerIdle >= 2)
		{
			playerIdle = 0;
		}
	}

	if (intervaSceneCount < SCENE_INTERVAL)
	{
		intervaSceneCount++;
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
	//背景
	DrawGraph(0, 0, ResourceManager::GetImage("GameClear/BackGround1"), TRUE);
	DrawGraph(0, 0, ResourceManager::GetImage("GameClear/BackGround2"), TRUE);
	DrawGraph(0, 0, ResourceManager::GetImage("GameClear/BackGround3"), TRUE);
	//地面
	for (int i = 0; i < 14; i++)
	{
		DrawGraph(0 + (i * 96), SCREEN_HEIGHT - 48, ResourceManager::GetImage("GameClear/Tile"), TRUE);
	}

	//おめでとうテキスト
	DrawGraph(360, 120, ResourceManager::GetImage("GameClear/CongratulationsText"), TRUE);

	//プレイヤー
	DrawRotaGraph(650, 625, 1, 0, ResourceManager::GetDivImage("Player/player", playerIdle), TRUE);
}

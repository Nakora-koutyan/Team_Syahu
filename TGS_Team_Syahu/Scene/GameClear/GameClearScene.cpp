#include "GameClearScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Scene/Title/TitleScene.h"
#include"../../Utility/common.h"
#include"../../Actor/Camera/Camera.h"

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
		if ((KeyInput::GetKey(KEY_INPUT_SPACE) || 
			PadInput::OnButton(XINPUT_BUTTON_A)|| PadInput::OnButton(XINPUT_BUTTON_B)||
			PadInput::OnButton(XINPUT_BUTTON_X)|| PadInput::OnButton(XINPUT_BUTTON_Y)))
		{
			return new TitleScene();
		}
	}

	return this;
}

void GameClearScene::Draw() const
{
	//背景
	for (int i = 0; i < 2; i++)
	{
		DrawGraphF(Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).x,
			Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).y,
			ResourceManager::GetImage("GameClear/BackGround1"), TRUE);
		DrawGraphF(Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).x,
			Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).y,
			ResourceManager::GetImage("GameClear/BackGround2"), TRUE);
		DrawGraphF(Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).x,
			Camera::ConvertScreenPosition({ 0.f + (i * 2560),0.f }).y,
			ResourceManager::GetImage("GameClear/BackGround3"), TRUE);
	}
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

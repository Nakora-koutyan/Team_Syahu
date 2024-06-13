#include"EndScene.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../Utility/common.h"

EndScene::EndScene()
{
	intervaSceneCount = 0;
}

EndScene::~EndScene()
{

}

void EndScene::Initialize()
{

}

void EndScene::Finalize()
{

}

SceneBase* EndScene::Update()
{
	if (intervaSceneCount < SCENE_INTERVAL * 4)
	{
		intervaSceneCount++;
	}
	else
	{
		return nullptr;
	}

	return this;
}

void EndScene::Draw() const
{
	//背景
	DrawGraph(0, 0, ResourceManager::GetImage("Stage/Background/layer_1"), TRUE);
	DrawGraph(0, 198, ResourceManager::GetImage("Stage/Background/layer_2"), TRUE);
	
	if (intervaSceneCount < SCENE_INTERVAL * 2)
	{
		DrawGraph(0, 0, ResourceManager::GetImage("End/credit"), TRUE);
	}
	else
	{
		DrawGraph(400, 340, ResourceManager::GetImage("End/thanks"), TRUE);
	}
}

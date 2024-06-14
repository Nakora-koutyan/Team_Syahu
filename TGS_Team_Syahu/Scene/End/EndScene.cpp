#include"EndScene.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Utility/common.h"

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
	if (intervaSceneCount < SCENE_INTERVAL + 30)
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
	DrawGraph(0, 0, ResourceManager::GetImage("Stage/Background/layer_1"), TRUE);
	DrawString(300, 500, "credit", 0xffffff);
}

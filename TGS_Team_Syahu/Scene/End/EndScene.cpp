#include "EndScene.h"

EndScene::EndScene()
{
	intervalCount = 0;
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
	if (intervalCount < SCENE_INTERVAL)
	{
		intervalCount++;
	}
	else
	{
		return nullptr;
	}

	return this;
}

void EndScene::Draw() const
{
	DrawString(300, 500, "credit", 0xffffff);
}

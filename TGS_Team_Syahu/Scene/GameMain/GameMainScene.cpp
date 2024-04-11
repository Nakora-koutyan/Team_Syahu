#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
}

SceneBase* GameMainScene::Update()
{
	camera->Update(this);

	player->Update(this);

	return this;
}

void GameMainScene::Draw() const
{
	DebugStage();

	camera->Draw();

	player->Draw();

}

void GameMainScene::DebugStage() const
{
	Vector2D pos1 = {};
	Vector2D pos2 = {};

	//xé≤ÇÃê¸
	pos1 = { 0.f, 0.f };
	pos2 = { WORLD_WIDTH / 2.0f, 0.f };

	for (int i = 0; i <= LINE_NUM; i++)
	{
		DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, 0xffffff);
		pos1.y += WORLD_HEIGHT / (LINE_NUM / 1.5f);
		pos2.y += WORLD_HEIGHT / (LINE_NUM / 1.5f);
	}

	//yé≤ÇÃê¸
	pos1 = { 0.f, 0.f };
	pos2 = { 0.f, WORLD_HEIGHT };
	for (int i = 0; i < LINE_NUM; i++)
	{
		DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, 0xffffff);
		pos1.x += WORLD_WIDTH / (LINE_NUM);
		pos2.x += WORLD_WIDTH / (LINE_NUM);
	}
}

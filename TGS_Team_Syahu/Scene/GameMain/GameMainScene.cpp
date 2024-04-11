#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new NormalEnemy();

	kari = LoadGraph("Resource/Images/kari.png");
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
	delete enemy;
}

SceneBase* GameMainScene::Update()
{
	camera->Update(this);

	player->Update(this);

	enemy->Update(this);

	return this;
}

void GameMainScene::Draw() const
{
	DrawGraphF(GetCamera()->ConvertScreenPosition({ 0,0 }).x, GetCamera()->ConvertScreenPosition({ 0,0 }).y, kari, TRUE);

	DebugStage();

	camera->Draw();

	player->Draw();

	enemy->Draw();

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

	//xé≤ÇÃê¸
	pos1 = { 0.f, GROUND_LINE };
	pos2 = { WORLD_WIDTH, GROUND_LINE };
	DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, 0xff0000);

}

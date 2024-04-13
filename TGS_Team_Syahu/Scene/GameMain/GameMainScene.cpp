#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new NormalEnemy();
	enemy->Initialize();

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
		
	if (enemy != nullptr)
	{
		enemy->Update(this);

		//deleteしなくてもいい
		if (enemy->GetHp() <= 0.f)
		{
			delete enemy;
			enemy = nullptr;
		}
	}

	return this;
}

void GameMainScene::Draw() const
{
	DrawGraphF(GetCamera()->ConvertScreenPosition({ 0,0 }).x, GetCamera()->ConvertScreenPosition({ 0,0 }).y, kari, TRUE);

	//x軸
	Vector2D pos1 = { 0.f, GROUND_LINE };
	Vector2D pos2 = { WORLD_WIDTH, GROUND_LINE };
	DrawLineAA
	(GetCamera()->ConvertScreenPosition(pos1).x, GetCamera()->ConvertScreenPosition(pos1).y,
	GetCamera()->ConvertScreenPosition(pos2).x, GetCamera()->ConvertScreenPosition(pos2).y,
	0xffffff
	);

	camera->Draw();

	player->Draw();

	if (enemy != nullptr)
	{
		enemy->Draw();
	}

}

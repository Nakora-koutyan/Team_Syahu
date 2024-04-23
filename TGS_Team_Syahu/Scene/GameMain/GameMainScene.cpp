#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new NormalEnemy();
	enemy->Initialize();
	stageblock = new StageBlock();

	kari = LoadGraph("Resource/Images/kari.png");

	debugModeFlg = false;
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
	delete enemy;
	delete stageblock;
}

SceneBase* GameMainScene::Update()
{
	if (KeyInput::GetKey(KEY_INPUT_G))debugModeFlg = !debugModeFlg;

	camera->Update(player->GetLocation(),debugModeFlg);

	player->Update();

	HitCheck();
		
	if (enemy != nullptr)
	{
		enemy->Update(player);

		//deleteしなくてもいい
		if (enemy->GetHp() <= 0.f)
		{
			delete enemy;
			enemy = nullptr;
		}
	}

	stageblock->Update();

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

	stageblock->Draw();
}

void GameMainScene::HitCheck()
{
	//雑魚敵がnullじゃないなら
	if (enemy != nullptr)
	{	
		//雑魚敵とプレイヤーが当たったら
		if (player->CollisionCheck(enemy))
		{
			player->Hit(enemy);
			enemy->SetIsKnockBack(true);
			if (enemy->GetCenterLocation().x < player->GetCenterLocation().x)
			{
				enemy->SetMove({ -2.f,0.f });
			}
			else
			{
				enemy->SetMove({ 2.f,0.f });
			}
		}

		//雑魚敵と投げるが当たったら
		if (player->GetNormalWeapon()->CollisionCheck(enemy))
		{
			player->GetNormalWeapon()->Hit(enemy, player);
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵と奪うが当たったら
		for (int i = 0; i < STEAL_VALUE; i++)
		{
			if (player->GetSteal(i)->CollisionCheck(enemy))
			{
				player->GetSteal(i)->Hit(enemy, player);
				enemy->SetIsKnockBack(true);
			}
		}

		//雑魚敵と大剣が当たったら
		if (player->GetLargeSword()->CollisionCheck(enemy))
		{
			player->GetLargeSword()->Hit(enemy, player);
			enemy->SetIsKnockBack(true);
		}
	}
}

#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new NormalEnemy();
	enemy->Initialize();
	stageblock = new StageBlock();
	ui = new UI();

	kari = LoadGraph("Resource/Images/kari.png");

	debugModeFlg = false;
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
	delete enemy;
	delete stageblock;
	delete ui;
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

	ui->Update(player);

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

	ui->Draw();

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
		if (player->GetSteal()->CollisionCheck(enemy) ||
			player->GetSteal()->GetSideClaw(0).CollisionCheck(enemy) ||
			player->GetSteal()->GetSideClaw(1).CollisionCheck(enemy))
		{
			player->GetSteal()->Hit(enemy, player);
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵と大剣が当たったら
		if (player->GetLargeSword()->CollisionCheck(enemy))
		{
			player->GetLargeSword()->Hit(enemy, player);
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵と短剣が当たったら
		if (player->GetDagger()->CollisionCheck(enemy))
		{
			player->GetDagger()->Hit(enemy, player);
			enemy->SetIsKnockBack(true);
		}

		// ブロックと敵が当たったら
		if (stageblock->CollisionCheck(enemy))
		{
			// 座標、移動量取得
			Vector2D EnemyLoc = enemy->GetLocation();
			Vector2D BlockLoc = stageblock->GetLocation();
			Vector2D move = enemy->GetMove();
			// 上から
			if ((EnemyLoc.y + 64) <= BlockLoc.y && enemy->GetDirection().y >= 0.f) {
				EnemyLoc.y = BlockLoc.y - 84;
				enemy->SetLocation(EnemyLoc);
				move.y = 0;
				enemy->SetMove(move);
			}
			// 下から
			else if (EnemyLoc.y >= (BlockLoc.y + 90) && enemy->GetDirection().y <= 0.f) {
				EnemyLoc.y = BlockLoc.y + 100;
				enemy->SetLocation(EnemyLoc);
				move.y = 0;
				enemy->SetMove(move);
			}
			else {
				// 右から
				if (EnemyLoc.x >= (BlockLoc.x + 50)) {
					EnemyLoc.x = BlockLoc.x + 100;
					EnemyLoc.y = EnemyLoc.y;
					enemy->SetLocation(EnemyLoc);
				}
				// 左から
				else {
					EnemyLoc.x = BlockLoc.x - 56.f;
					enemy->SetLocation(EnemyLoc);
				}
				move.x = 0;
				enemy->SetMove(move);
			}
		}
	}
	// ブロックとプレイヤーが当たったら
	if (stageblock->CollisionCheck(player))
	{
		// 座標、移動量取得
		Vector2D PlayerLoc = player->GetLocation();
		Vector2D BlockLoc = stageblock->GetLocation();
		Vector2D move = player->GetMove();
		// 上から
		if ((PlayerLoc.y + 64) <= BlockLoc.y && player->GetDirection().y >= 0.f) {
			player->Landing(BlockLoc.y);
		}
		// 下から
		else if (PlayerLoc.y >= (BlockLoc.y + 90) && player->GetDirection().y <= 0.f) {
			PlayerLoc.y = BlockLoc.y + 100;
			player->SetLocation(PlayerLoc);
			move.y = 0;
			player->SetMove(move);
		}
		else {
			// 右から
			if (PlayerLoc.x >= (BlockLoc.x + 50)) {
				PlayerLoc.x = BlockLoc.x + 100;
				player->SetLocation(PlayerLoc);
			}
			// 左から
			else {
				PlayerLoc.x = BlockLoc.x - 56.f;
				player->SetLocation(PlayerLoc);
			}
			move.x = 0;
			player->SetMove(move);
		}
	}
}

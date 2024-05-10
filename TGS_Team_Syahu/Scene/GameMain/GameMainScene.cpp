#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
	:player(nullptr),camera(nullptr),enemy(nullptr),stageblock(nullptr),ui(nullptr),enemy1(nullptr)
	,debugModeFlg(false)
{
	kari = LoadGraph("Resource/Images/kari.png");
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	player = new Player();
	player->Initialize();
	camera = new Camera();
	enemy = new NormalEnemy();
	enemy->Initialize();
	enemy1 = new LargeSwordEnemy();
	enemy1->Initialize();
	stageblock = new StageBlock();
	ui = new UI();
}

void GameMainScene::Finalize()
{
	delete player;
	delete camera;
	delete enemy;
	delete stageblock;
	delete ui;
	delete enemy1;
}

SceneBase* GameMainScene::Update()
{
	if (KeyInput::GetKey(KEY_INPUT_G))debugModeFlg = !debugModeFlg;

	camera->Update(player->GetLocation(),debugModeFlg);

	player->Update();

	HitCheck();
		
	if (enemy != nullptr)
	{
		enemy->Update();
		enemy->FindPlayer(player);

		//deleteしなくてもいい
		if (enemy->GetHp() <= 0.f)
		{
			delete enemy;
			enemy = nullptr;
		}
	}
	enemy1->Update();

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

	player->Draw();

	if (enemy != nullptr)
	{
		enemy->Draw();
	}

	enemy1->Draw();

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
			player->Hit(enemy, enemy->GetDamage());
		}

		//雑魚敵と投げるが当たったら
		if (player->GetNormalWeapon()->CollisionCheck(enemy))
		{
			player->GetNormalWeapon()->Hit(enemy, player->GetDamage());
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵と奪うが当たったら
		if (player->GetSteal()->CollisionCheck(enemy) ||
			player->GetSteal()->GetSideClaw(0).CollisionCheck(enemy) ||
			player->GetSteal()->GetSideClaw(1).CollisionCheck(enemy))
		{
			player->GetSteal()->Hit(enemy, player->GetDamage());
		}

		//雑魚敵と大剣が当たったら
		if (player->GetLargeSword()->CollisionCheck(enemy))
		{
			player->GetLargeSword()->Hit(enemy, player->GetDamage());
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵と短剣が当たったら
		if (player->GetDagger()->CollisionCheck(enemy))
		{
			player->GetDagger()->Hit(enemy, player->GetDamage());
			enemy->SetIsKnockBack(true);
		}

		//雑魚敵とレイピアが当たったら
		if (player->GetRapier()->CollisionCheck(enemy))
		{
			player->GetRapier()->Hit(enemy, player->GetDamage());
			enemy->SetIsKnockBack(true);
		}

		// ブロックと敵が当たったら
		if (stageblock->CollisionCheck(enemy))
		{
			// 座標、移動量取得
			Vector2D EnemyLoc = enemy->GetLocation();
			Vector2D BlockLoc = stageblock->GetLocation();
			Vector2D move = enemy->GetMove();
			Area EnemySize = enemy->GetArea();
			Area BlockSize = stageblock->GetArea();
			// 上から
			if ((EnemyLoc.y + EnemySize.height - 20) <= BlockLoc.y && enemy->GetDirection().y >= 0.f) {
				EnemyLoc.y = BlockLoc.y - EnemySize.height;
				enemy->SetLocation(EnemyLoc);
				move.y = 0;
				enemy->SetMove(move);
			}
			// 下から
			else if (EnemyLoc.y >= BlockLoc.y + BlockSize.height - 10 && enemy->GetDirection().y <= 0.f) {
				EnemyLoc.y = BlockLoc.y + BlockSize.height;
				enemy->SetLocation(EnemyLoc);
				move.y = 0;
				enemy->SetMove(move);
			}
			else {
				// 右から
				if (EnemyLoc.x >= (BlockLoc.x + BlockSize.width / 2)) {
					EnemyLoc.x = BlockLoc.x + BlockSize.width;
					EnemyLoc.y = EnemyLoc.y;
					enemy->SetLocation(EnemyLoc);
				}
				// 左から
				else {
					EnemyLoc.x = BlockLoc.x - EnemySize.width;
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
		Area PlayerSize = player->GetArea();
		Area BlockSize = stageblock->GetArea();
		// 上から
		if ((PlayerLoc.y + PlayerSize.height - 20) <= BlockLoc.y && player->GetDirection().y >= 0.f) {
			int Dropwidth = 21;
			if (move.x != 0 || (PlayerLoc.x + PlayerSize.width - Dropwidth <= BlockLoc.x + BlockSize.width && PlayerLoc.x + Dropwidth >= BlockLoc.x)) {
				player->Landing(BlockLoc.y);
			}
		}
		// 下から
		else if (PlayerLoc.y >= (BlockLoc.y + BlockSize.height - 10) && player->GetDirection().y <= 0.f) {
			PlayerLoc.y = BlockLoc.y + BlockSize.height;
			player->SetLocation(PlayerLoc);
			move.y = 0;
			player->SetMove(move);
		}
		else {
			// 右から
			if (PlayerLoc.x >= BlockLoc.x + BlockSize.width / 2) {
				PlayerLoc.x = BlockLoc.x + BlockSize.width;
				player->SetLocation(PlayerLoc);
			}
			// 左から
			else {
				PlayerLoc.x = BlockLoc.x - PlayerSize.width;
				player->SetLocation(PlayerLoc);
			}
			move.x = 0;
			player->SetMove(move);
		}
	}
}

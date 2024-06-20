#include"../../Utility/common.h"
#include"GameMainScene.h"
#include"../../Actor/Character/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Character/Enemy/NormalEnemy.h"
#include"../../Actor/Character/Enemy/LargeSwordEnemy.h"
#include"../../Actor/Character/Enemy/DaggerEnemy.h"
#include"../../Map/StageBlock.h"
#include"../../Map/BlockDeta.h"
#include"../Edit/Edit.h"
#include"../Help/HelpScene.h"
#include"../../ResourceManager/ResourceManager.h"
#include"../../Scene/GameOver/GameOverScene.h"
#include"../../Scene/GameClear/GameClearScene.h"

GameMainScene::GameMainScene() :ui(nullptr)
{

}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	ui = new UI();

	object.push_back(new Player);
	object.push_back(new Camera);

	createStage();

	for (ObjectBase* ob : object)
	{
		ob->Initialize();
	}
}

void GameMainScene::Finalize()
{
	for (ObjectBase* ob : object)
	{
		if (ob != nullptr)
		{
			ob->Finalize();
			delete ob;
		}
	}
	delete ui;
}

SceneBase* GameMainScene::Update()
{
	ResourceManager::PlayBGM("gamemain");

	for (auto i = 0; i < object.size(); i++)
	{
		if (object[i] !=  nullptr)
		{
			const Player* player = static_cast<const Player*>(object[0]);

			//カメラなら
			if (object[i]->GetObjectType() == ObjectType::Camera && object[i - 1] != nullptr)
			{
				Camera* camera = static_cast<Camera*>(object[i]);
				ui->Update(player);
				camera->SetTarget(object[i - 1]->GetLocation());
			}

			if (object[i]->GetObjectType() == ObjectType::Enemy && player->GetEquipmentAnimFlg())
			{
				//プレイヤーの装備アニメーション中は敵の更新をしない
			}
			else
			{
				object[i]->Update();
				if (object[i]->GetObjectType() == ObjectType::Player || object[i]->GetObjectType() == ObjectType::Enemy)
				{
					CharaBase* chara = static_cast<CharaBase*>(object[i]);
					chara->MovementUpdate();
				}
			}

			if (object[i]->GetObjectType() == ObjectType::Player || object[i]->GetObjectType() == ObjectType::Enemy)
			{
				const CharaBase* chara = static_cast<const CharaBase*>(object[i]);
				//プレイヤーなら
				if (object[i]->GetObjectType() == ObjectType::Player)
				{
					const Player* player = static_cast<const Player*>(object[i]);
					if (player->GetMaxLocation().x >= WORLD_WIDTH)
					{
						return new GameClearScene();
					}
				}
				//敵なら
				if (object[i]->GetObjectType() == ObjectType::Enemy)
				{
					EnemyBase* enemy = static_cast<EnemyBase*>(object[i]);
					enemy->FindPlayer(player);
				}
				//プレイヤーか敵の死亡フラグがたったら
				if (chara->GetDeathFlg())
				{
					//プレイヤーならゲームオーバーに遷移（今はゲームメイン）
					if (chara->GetObjectType() == ObjectType::Player)
					{
						ResourceManager::SetPositionAllBGM(0);
						return new GameOverScene();
					}
					delete object[i];
					object[i] = nullptr;
				}
			}
		}
	}

	HitCheck();

#ifdef DEBUG

	if (KeyInput::GetKey(KEY_INPUT_L)) {
		return new Edit();
	}

	if (KeyInput::GetKey(KEY_INPUT_H))
	{
		return new HelpScene();
	}

#endif // DEBUG

	return this;
}

void GameMainScene::Draw() const
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

	for (ObjectBase* ob : object)
	{
		if (ob != nullptr)
		{
			ob->Draw();
			if (ob->GetObjectType() == ObjectType::Enemy)
			{
				EnemyBase* enemy = static_cast<EnemyBase*>(ob);
				if (enemy->GetEnemyStatus() != EnemyStatus::Death)
				{
					ui->EnemyHPBar(enemy->GetScreenLocation(), enemy->GetHp());
				}
			}
		}
	}

	ui->Draw();
}

void GameMainScene::HitCheck()
{
	for (auto i = 0; i < object.size(); i++)
	{
		for (auto j = 0; j < object.size(); j++)
		{
			//i,j番目がnullじゃないかつコリジョンがあるなら
			if (object[i] != nullptr && object[j] != nullptr &&
				object[i]->GetCollisionType() != CollisionType::None &&
				object[j]->GetCollisionType() != CollisionType::None)
			{
				//i番目がプレイヤーなら武器の当たり判定
				if (object[i]->GetObjectType() == ObjectType::Player)
				{
					HitCheckPlayerWeapon(i, j);
				}
				//j番目がエネミーなら武器の当たり判定
				if (object[j]->GetObjectType() == ObjectType::Enemy)
				{
					HitCheckEnemyWeapon(i, j);
				}
				
				//ゲームメインにあるオブジェクトの当たり判定
				if (object[i] != object[j] &&
					//object[i]->InScreen() && object[j]->InScreen() &&
					object[i]->CollisionCheck(object[j]))
				{
					//ステージの場合
					if (object[j]->GetObjectType() == ObjectType::Object)
					{
						//ステージのHitを呼ぶ
						object[j]->Hit(object[i], 0.f);
					}
					//ステージじゃないなら
					else
					{
						if (object[j]->GetObjectType() != ObjectType::Player)
						{
							object[i]->Hit(object[j], object[j]->GetDamage());
						}
						else
						{
							object[i]->Hit(object[j], 0);
						}
					}
				}
			}
		}
	}
}

void GameMainScene::HitCheckPlayerWeapon(const int i, const int j)
{
	const Player* player = static_cast<const Player*>(object[i]);
	//武器と敵の当たり判定
	if (object[j]->GetObjectType() == ObjectType::Enemy)
	{
		EnemyBase* enemy = static_cast<EnemyBase*>(object[j]);

		for (auto k = 0; k < player->GetWeaponSize(); k++)
		{
			if (player->GetWeapon(k)->GetIsShow())
			{
				//武器のポインタが格納されている配列の要素を呼ぶ
				if (player->GetWeapon(k)->CollisionCheck(enemy))
				{
					player->GetWeapon(k)->Hit(enemy, player->GetDamage());
					enemy->Hit(object[i], 0);
				}
			}
		}
		//奪うだけ特殊なので直接呼ぶ
		if (player->GetSteal()->GetIsShow()&&
			(player->GetSteal()->CollisionCheck(object[j]) ||
				player->GetSteal()->GetSideClaw(0).CollisionCheck(object[j]) ||
				player->GetSteal()->GetSideClaw(1).CollisionCheck(object[j])))
		{
			player->GetSteal()->Hit(object[j], player->GetDamage());
			enemy->Hit(object[i], 0);
		}
	}
	//短剣とオブジェクトの当たり判定
	if (object[j]->GetObjectType() == ObjectType::Object)
	{
		for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
		{
			if (player->GetDagger(i)->GetIsShow() &&
				player->GetDagger(i)->CollisionCheck(object[j]))
			{
				player->GetDagger(i)->Init();
			}
		}
	}
}

void GameMainScene::HitCheckEnemyWeapon(const int i, const int j)
{
	EnemyBase* enemy = static_cast<EnemyBase*>(object[j]);
	Player* player = static_cast<Player*>(object[0]);

	if (enemy->GetEnemyType() == EnemyType::LargeSwordEnemy)
	{
		LargeSwordEnemy* largeSwordEnemy = static_cast<LargeSwordEnemy*>(object[j]);

		if (largeSwordEnemy->GetLargeSwordCollisionBox()->CollisionCheck(player) &&
			largeSwordEnemy->GetSignToAttack())
		{
			largeSwordEnemy->HitWeapon(player);
			player->Hit(largeSwordEnemy, largeSwordEnemy->GetDamage() * 3);
		}
	}
	if (enemy->GetEnemyType() == EnemyType::DaggerEnemy)
	{
		DaggerEnemy* daggerEnemy = static_cast<DaggerEnemy*>(object[j]);
		if (daggerEnemy->GetDagger()->CollisionCheck(player) && daggerEnemy->GetSignToAttack())
		{
			daggerEnemy->HitWeapon(player);
			player->Hit(daggerEnemy, daggerEnemy->GetDamage() * 3);
		}

		//短剣とオブジェクトの当たり判定
		if (object[i]->GetObjectType() == ObjectType::Object)
		{
			for (int k = 0; k < PLAYER_MAX_DAGGER; k++)
			{
				if (daggerEnemy->GetDagger()->CollisionCheck(object[i]))
				{
					daggerEnemy->GetDagger()->Init();
				}
			}
		}
	}
	if (enemy->GetEnemyType() == EnemyType::RapierEnemy)
	{
		NormalEnemy* normalEnemy = static_cast<NormalEnemy* > (object[j]);
		if (normalEnemy->GetRapier()!=nullptr && normalEnemy->GetRapier()->CollisionCheck(player) 
			&& normalEnemy->GetSignToAttack() &&normalEnemy->GetWeaponType() == Weapon::Rapier)
		{
			normalEnemy->HitWeapon(player);
			player->Hit(normalEnemy, normalEnemy->GetDamage() * 3);
		}
	}
}

void GameMainScene::createStage() {
	std::string fname;
	std::string fpassCoupling = "Resource/StageData/";
	std::string fpass;

	switch (NOW_LOAD_STAGE)
	{
	case 0:
		fname = "FirstStage.txt";
		break;
	case 1:
		fname = "SecondStage.txt";
		break;
	case 2:
		fname = "ThirdStage.txt";
		break;
	default:
		break;
	}

	// 文字列の連結
	fpass = fpassCoupling + fname;
	int stageWidth;
	int stageHeight;
	int stageData[WORLD_BLOCK_X][WORLD_BLOCK_Y];
	std::ifstream file(fpass.c_str());
	if (file)
	{
		file >> stageWidth;
		file >> stageHeight;
		for (int i = 0; i < stageHeight; i++)
		{
			for (int j = 0; j < stageWidth; j++)
			{
				file >> stageData[j][i];
				switch (stageData[j][i])
				{
				case 0:
					break;
				case 1:
					// 敵(ソード)生成
					object.push_back(new LargeSwordEnemy(BLOCK_WIDTH * j, BLOCK_HEIGHT * i));
					break;
				case 2:
					// 敵(レイピア)生成
					object.push_back(new NormalEnemy(BLOCK_WIDTH * j, BLOCK_HEIGHT * i));
					break;
				case 3:
					// 敵(ダガー)生成
					object.push_back(new DaggerEnemy(BLOCK_WIDTH * j, BLOCK_HEIGHT * i));
					break;
				default:
					// ブロック生成
					object.push_back(new StageBlock(BLOCK_WIDTH * j, BLOCK_HEIGHT * i, stageData[j][i] - 4));
					break;
				}
			}
		}
	}
}
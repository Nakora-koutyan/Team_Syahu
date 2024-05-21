#include"../../Utility/common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene() :ui(nullptr), debugModeFlg(false)
{
	kari = LoadGraph("Resource/Images/kari.png");
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	ui = new UI();

	object.push_back(new Player);
	object.push_back(new Camera);
	object.push_back(new NormalEnemy);
	object.push_back(new LargeSwordEnemy);
	object.push_back(new StageBlock);

	for (ObjectBase* ob : object)
	{
		ob->Initialize();
	}
}

void GameMainScene::Finalize()
{
	for (ObjectBase* ob : object)
	{
		delete ob;
	}
}

SceneBase* GameMainScene::Update()
{
	if (KeyInput::GetKey(KEY_INPUT_G))debugModeFlg = !debugModeFlg;

	HitCheck();

	for (int i = 0; i < object.size(); i++)
	{
		if (object[i] !=  nullptr)
		{
			//カメラなら
			if (object[i]->GetObjectType() == ObjectType::Camera && object[i - 1] != nullptr)
			{
				Camera* camera = static_cast<Camera*>(object[i]);
				//カメラの前にプレイヤーが格納されている
				Player* player = static_cast<Player*>(object[i - 1]);
				ui->Update(player);
				camera->SetTarget(object[i - 1]->GetLocation());
			}

			object[i]->Update();

			if (object[i]->GetObjectType() == ObjectType::Player || object[i]->GetObjectType() == ObjectType::Enemy)
			{
				const CharaBase* chara = static_cast<const CharaBase*>(object[i]);
				//敵なら
				if (object[i]->GetObjectType() == ObjectType::Enemy)
				{
					EnemyBase* enemy = static_cast<EnemyBase*>(object[i]);
					Player* player = static_cast<Player*>(object[0]);
					enemy->FindPlayer(player);
				}
				//プレイヤーか敵の死亡フラグがたったら
				if (chara->GetDeathFlg())
				{
					//プレイヤーならゲームオーバーに遷移（今はゲームメイン）
					if (chara->GetObjectType() == ObjectType::Player)
					{
						return new GameMainScene();
					}
					delete object[i];
					object[i] = nullptr;
				}
			}
		}
	}

	return this;
}

void GameMainScene::Draw() const
{
	DrawGraphF(Camera::ConvertScreenPosition({ 0,0 }).x, Camera::ConvertScreenPosition({ 0,0 }).y, kari, TRUE);

	//x軸
	Vector2D pos1 = { 0.f, GROUND_LINE };
	Vector2D pos2 = { WORLD_WIDTH, GROUND_LINE };
	DrawLineAA
	(Camera::ConvertScreenPosition(pos1).x, Camera::ConvertScreenPosition(pos1).y,
		Camera::ConvertScreenPosition(pos2).x, Camera::ConvertScreenPosition(pos2).y,
		0xffffff
	);

	ui->Draw();

	for (ObjectBase* ob : object)
	{
		if (ob != nullptr)
		{
			ob->Draw();
			if (ob->GetObjectType() == ObjectType::Enemy)
			{
				EnemyBase* enemy = static_cast<EnemyBase*>(ob);
				ui->EnemyHPBar(enemy->GetScreenLocation(), enemy->GetHp());
			}
		}
	}
}

void GameMainScene::HitCheck()
{
	for (int i = 0; i < object.size(); i++)
	{
		for (int j = i + 1; j < object.size(); j++)
		{
			//i,j番目がnullじゃないかつコリジョンがあるなら
			if (object[i] && object[j] != nullptr && object[j]->GetCollisionType() != CollisionType::None)
			{
				//i番目がプレイヤーなら武器の当たり判定
				if (object[i]->GetObjectType() == ObjectType::Player)
				{
					HitCheckPlayerWeapon(i, j);
				}
				//j番目がエネミーなら武器の当たり判定
				if (object[j]->GetObjectType() == ObjectType::Enemy)
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
				}
				
				//ゲームメインにあるオブジェクトの当たり判定
				if (object[i]->CollisionCheck(object[j]))
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
						object[i]->Hit(object[j], object[j]->GetDamage());
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
	if (object[j]->GetObjectType() == ObjectType::Enemy && player->GetIsAttack())
	{
		CharaBase* enemy = static_cast<CharaBase*>(object[j]);

		for (int k = 0; k < 5; k++)
		{
			if (k != 1)
			{
				//武器のポインタが格納されている配列の要素を呼ぶ
				if (player->GetWeapon(k)->CollisionCheck(enemy))
				{
					player->GetWeapon(k)->Hit(enemy, player->GetDamage());
					enemy->Hit(object[i], 0);
				}
			}
			//奪うだけ特殊なので直接呼ぶ
			else
			{
				if (player->GetSteal()->CollisionCheck(object[j]) ||
					player->GetSteal()->GetSideClaw(0).CollisionCheck(object[j]) ||
					player->GetSteal()->GetSideClaw(1).CollisionCheck(object[j]))
				{
					player->GetSteal()->Hit(object[j], player->GetDamage());
					enemy->Hit(object[i], 0);
				}
			}
		}
	}
	//投げるとオブジェクトの当たり判定
	if (object[j]->GetObjectType() == ObjectType::Object)
	{
		if (player->GetNormalWeapon()->CollisionCheck(object[j]))
		{
			player->GetNormalWeapon()->Initialize();
		}
	}
}

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
			if (object[i]->GetObjectType() == ObjectType::None && object[0] != nullptr)
			{
				Camera* camera = static_cast<Camera*>(object[i]);
				Player* player = static_cast<Player*>(object[0]);
				ui->Update(player);
				camera->SetTarget(object[0]->GetLocation());
			}

			object[i]->Update();

			if (object[i]->GetObjectType() == ObjectType::Player || object[i]->GetObjectType() == ObjectType::Enemy)
			{
				const CharaBase* chara = static_cast<const CharaBase*>(object[i]);
				//プレイヤーか敵のHPが0以下なら
				if (chara->GetHp() <= 0.f)
				{
					delete object[i];
					object[i] = nullptr;
				}
			}
		}
	}

#ifdef DEBUG

	if (KeyInput::GetKey(KEY_INPUT_L)) {
		return new Edit();
	}

#endif // DEBUG


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
		}
	}
}

void GameMainScene::HitCheck()
{
	for (int i = 0; i < object.size(); i++)
	{
		//i番目がnullじゃないかつオブジェクトタイプがあるなら
		if (object[i] != nullptr && object[i]->GetObjectType() != ObjectType::None)
		{
			for (int j = i + 1; j < object.size(); j++)
			{
				//j番目がnullじゃないかつオブジェクトタイプがあるなら
				if (object[j] != nullptr && object[j]->GetObjectType() != ObjectType::None)
				{
					//i番目がプレイヤーなら
					if (object[i]->GetObjectType() == ObjectType::Player)
					{
						const Player* player = static_cast<const Player*>(object[i]);
						//武器との当たり判定
						if (object[j]->GetObjectType() == ObjectType::Enemy && player->GetIsAttack())
						{
							CharaBase* enemy = static_cast<CharaBase*>(object[j]);

							if (player->GetNormalWeapon()->CollisionCheck(object[j]))
							{
								enemy->Hit(object[i], player->GetNormalWeapon()->GetDamage());
							}

							if (player->GetSteal()->CollisionCheck(object[j]) ||
								player->GetSteal()->GetSideClaw(0).CollisionCheck(object[j]) ||
								player->GetSteal()->GetSideClaw(1).CollisionCheck(object[j]))
							{
								player->GetSteal()->Hit(object[j], 0);
								enemy->Hit(object[i], player->GetSteal()->GetDamage());
							}

							if (player->GetLargeSword()->CollisionCheck(object[j]))
							{
								enemy->Hit(object[i], player->GetLargeSword()->GetDamage());
							}

							if (player->GetDagger()->CollisionCheck(object[j]))
							{
								enemy->Hit(object[i], player->GetDagger()->GetDamage());
							}

							if (player->GetRapier()->CollisionCheck(object[j]))
							{
								enemy->Hit(object[i], player->GetRapier()->GetDamage());
							}
						}
					}
					if (object[i]->CollisionCheck(object[j]))
					{
						//ステージの場合
						if (object[j]->GetObjectType() == ObjectType::Object)
						{
							object[j]->Hit(object[i], 0.f);
						}
						else if (object[j]->GetObjectType() == ObjectType::Enemy)
						{
							const CharaBase* target = static_cast<const CharaBase*>(object[j]);
							//プレイヤーと敵の場合
							if ((object[i]->GetObjectType() == ObjectType::Player && target->GetObjectType() == ObjectType::Enemy))
							{
								object[i]->Hit(object[j], object[j]->GetDamage());
							}
						}
					}
				}
			}
		}
	}
}

#include "DaggerEnemy.h"
#include "../Player/Player.h"
#include "../../Camera/Camera.h"

//コンストラクタ
DaggerEnemy::DaggerEnemy() :drawnSword(false), dagger(nullptr), daggerEnemyAnimNumber{(0)}, 
daggerEnemyAnim{NULL},enemyAnimInterval(0),correctLocX(0.f),correctLocY(0.f),animTurnFlg(TRUE)
{
}
//デストラクタ
DaggerEnemy::~DaggerEnemy()
{
}

//初期化処理
void DaggerEnemy::Initialize()
{
	//画像配列の初期化
	daggerEnemyAnimNumber = 0;
	int daggerEnemyAnimNumberOld[60];
	LoadDivGraph("Resource/Images/Enemy/DaggerEnemy.png", 60, 12, 5, 160, 160, daggerEnemyAnimNumberOld);
	for (int i = 0; i < 60; i++)
	{
		//画像の存在しない部分を読み込まない
		if (6 <= i && 11 >= i ||
			30 <= i && 35 >= i ||
			46 <= i && 47 >= i ||
			55 <= i && 60 >= i)
		{
			//スキップ
			continue;
		}
		daggerEnemyAnim[daggerEnemyAnimNumber] = daggerEnemyAnimNumberOld[i];
		daggerEnemyAnimNumber++;
	}

	//サイズ{ x , y }
	area = { 80.f,85.f };
	//表示座標{ x , y }
	location = { 500,GROUND_LINE - area.height };

	//武器の種類：短剣
	weaponType = Weapon::Dagger;
	enemyType = EnemyType::DaggerEnemy;

	//体の向き
	direction.x = DIRECTION_LEFT;

	//体力
	hp = 100;
	//ダメージ
	damage = 5.f;

	//プレイヤーを見つけた？
	isFind = false;

	//エネミーの遷移状態
	enemyStatus = Patrol;

	//パトロールカウンターの初期設定
	patrolCounter = 0.f;

	//daggerクラスの生成
	dagger = new Dagger;

	//プレイヤーに攻撃を仕掛ける範囲
	attackCenser[0].x = GetMinLocation().x - 300.f;
	attackCenser[0].y = GetMinLocation().y - 25;
	attackCenser[1].x = GetMaxLocation().x + 300.f;
	attackCenser[1].y = GetMaxLocation().y + 25;

	correctLocX = 48.f;
	correctLocY = -48.f;

	daggerEnemyAnimNumber = 0;
	enemyAnimInterval = 0;
	signToAttack=false;
}

//更新処理
void DaggerEnemy::Update()
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(FPS * 0.2);
	KnockBack(this, FPS * 0.5, knockBackMove);

	switch (enemyStatus)
	{
	case EnemyStatus::Patrol:
		
		//パトロール処理
		EnemyPatrol();
		break;

	case EnemyStatus::AttackStandBy:
		
		//攻撃準備処理
		AttackStandBy();
		break;

	case EnemyStatus::AttackStart:
		
		//攻撃開始処理
		AttackStart();
		break;

	case EnemyStatus::AttackEnd:

		//攻撃終了処理
		AttackEnd();
		break;

	}
	//攻撃範囲更新
	AttackRange();

	//アニメーション処理
	EnemyAnimationManager();

	//画面端を越えない
	DontCrossBorder();

	//短剣の更新処理の呼び出し
	dagger->Update(this);

	location.x += move.x;
}

//描画
void DaggerEnemy::Draw() const
{
	//エネミーの描画
	DrawRotaGraphF(GetMinScreenLocation().x + correctLocX,
		GetMaxScreenLocation().y + correctLocY, 1, 0,
		daggerEnemyAnim[daggerEnemyAnimNumber], TRUE, animTurnFlg);

	dagger->Draw();

	//DrawFormatString(500, 600, 0xffff00, "%lf PatrolCounter", patrolCounter);
}

//プレイヤーをみつけた？
void DaggerEnemy::FindPlayer(const Player* player)
{
	if ((enemyStatus == EnemyStatus::Patrol ||
		enemyStatus == EnemyStatus::AttackStandBy) &&
		player->GetIsHit() == false)
	{
		//playerが一定の範囲にいるかどうか判定
		if (attackCenser[0].x <= player->GetMaxLocation().x &&
			attackCenser[1].x >= player->GetMinLocation().x &&
			attackCenser[0].y <= player->GetCenterLocation().y &&
			attackCenser[1].y >= player->GetCenterLocation().y)
		{
			//playerのいる方向を向く
			if (location.x >= player->GetCenterLocation().x)
			{
				//左向き
				direction.x = DIRECTION_LEFT;
				animTurnFlg = TRUE;
			}
			else if (location.x <= player->GetCenterLocation().x)
			{
				//右向き
				direction.x = DIRECTION_RIGHT;
				animTurnFlg = FALSE;
			}
			//見つけた？ -> Yes
			isFind = true;
		}
		else
		{
			//見つけた？ -> No
			isFind = false;
		}
	}
}

//攻撃の範囲
void DaggerEnemy::AttackRange()
{
	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 275.f;
	attackRange[0].y = GetCenterLocation().y;
	attackRange[1].x = GetMaxLocation().x + 275.f;
	attackRange[1].y = GetCenterLocation().y;
}


//パトロール処理
void DaggerEnemy::EnemyPatrol()
{
	//左向き
	if (direction.x == DIRECTION_LEFT)
	{
		move.x = -DAGGER_ENEMY_WALK_SPEED;
		patrolCounter -= DAGGER_ENEMY_WALK_SPEED;
		//左に200進んだら右向きにする
		if (patrolCounter <= -20.f)
		{
			direction.x = DIRECTION_RIGHT;
		}
	}
	//右向き
	else if (direction.x == DIRECTION_RIGHT)
	{
		move.x = DAGGER_ENEMY_WALK_SPEED;
		patrolCounter += DAGGER_ENEMY_WALK_SPEED;
		//右に200進んだら左向きにする
		if (patrolCounter >= 40.f)
		{
			direction.x = DIRECTION_LEFT;
		}
	}

	//プレイヤーを見つけたら攻撃準備に入る
	if (isFind)
	{
		enemyStatus = EnemyStatus::AttackStandBy;
		patrolCounter = 0.f;
	}
}

void DaggerEnemy::HitWeapon(ObjectBase* object)
{
	CharaBase* target = static_cast<CharaBase*>(object);

	if (signToAttack)
	{
		if (target->GetIsShow() && !target->GetIsHit())
		{
			target->SetKnockBackMove(DAGGER_ENEMY_KNOCKBACK);
		}
	}
}

//攻撃準備
void DaggerEnemy::AttackStandBy()
{
	//抜刀するまでの間、停止する
	move.x = 0.f;
	if (drawnSword == true)
	{
		//攻撃開始に遷移
		enemyStatus = EnemyStatus::AttackStart;
	}
}

//攻撃開始
void DaggerEnemy::AttackStart()
{
	move.x = 0;
	if (weaponType == Weapon::Dagger)
	{
		if (signToAttack)
		{
			dagger->Attack(this);
			enemyStatus = EnemyStatus::AttackEnd;
		}
	}
}

//攻撃終了
void DaggerEnemy::AttackEnd()
{
	move.x = 0;
	if (drawnSword == false)
	{
		enemyStatus = EnemyStatus::Patrol;
	}
}

//アニメーションマネージャー
void DaggerEnemy::EnemyAnimationManager()
{
	enemyAnimInterval++;
	if (enemyStatus == EnemyStatus::Patrol)
	{
		PatrolAnim();
	}
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		if (weaponType == Weapon::Dagger)
		{
			DaggerAttackStandByAnim();
		}
		else if (weaponType == Weapon::None)
		{
			WeaponNoneAttackStandByAnim();
		}
	}
	if (enemyStatus == EnemyStatus::AttackStart)
	{
		if (weaponType == Weapon::Dagger)
		{
			DaggerAttackStartAnim();
		}
		else if (weaponType == Weapon::None)
		{
			WeaponNoneAttackStartAnim();
		}
	}
	if (enemyStatus == EnemyStatus::AttackEnd)
	{
		if (weaponType == Weapon::Dagger)
		{
			DaggerAttackEndAnim();
		}
		else if (weaponType == Weapon::None)
		{
			WeaponNoneAttackEndAnim();
		}
	}
}

//パトロールアニメーション
void DaggerEnemy::PatrolAnim()
{
	if (daggerEnemyAnimNumber >= 5)
	{
		daggerEnemyAnimNumber = 0;
	}
	else if (enemyAnimInterval % 7 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

//攻撃準備時のアニメーション(短剣装備中)
void DaggerEnemy::DaggerAttackStandByAnim()
{
	//画像番号設定
	if (daggerEnemyAnimNumber < 7)
	{
		daggerEnemyAnimNumber = 6;
	}
	else if (daggerEnemyAnimNumber >= 11)
	{
		//仮の処理
		drawnSword = true;
	}

	//画像番号の更新
	if (enemyAnimInterval % 8 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}
//攻撃準備時のアニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackStandByAnim()
{
}

//攻撃開始アニメーション(短剣装備あり)
void DaggerEnemy::DaggerAttackStartAnim()
{
	if (daggerEnemyAnimNumber < 11)
	{
		daggerEnemyAnimNumber = 11;
	}
	else if (daggerEnemyAnimNumber >= 17)
	{
		daggerEnemyAnimNumber = 11;
		signToAttack = true;
	}

	if (enemyAnimInterval % 6 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}
//攻撃開始アニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackStartAnim()
{
}

//攻撃終了アニメーション(短剣装備あり)
void DaggerEnemy::DaggerAttackEndAnim()
{
}
//攻撃終了時アニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackEndAnim()
{
}

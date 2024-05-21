#include "DaggerEnemy.h"

//コンストラクタ
DaggerEnemy::DaggerEnemy():drawnSwordTime(0)
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

	//サイズ{ x , y }
	area = { 80.f,85.f };
	//表示座標{ x , y }
	location = { 1100,GROUND_LINE - area.height };

	//武器の種類：短剣
	weaponType = Weapon::Dagger;

	//体の向き
	direction.x = DIRECTION_LEFT;

	//体力
	hp = 110;
	//ダメージ
	damage = 5.f;

	//プレイヤーを見つけた？
	isFind = false;

	//エネミーの遷移状態
	enemyStatus = Patrol;

	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 275.f;
	attackRange[0].y = GetCenterLocation().y;
	attackRange[1].x = GetMaxLocation().x + 275.f;
	attackRange[1].y = GetCenterLocation().y;

	//プレイヤーに攻撃を仕掛ける範囲
	attackCenser[0].x = GetMinLocation().x - 300.f;
	attackCenser[0].y = GetMinLocation().y - 25;
	attackCenser[1].x = GetMaxLocation().x + 300.f;
	attackCenser[1].y = GetMaxLocation().y + 25;
}

//更新処理
void DaggerEnemy::Update()
{
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

	//アニメーション処理
	EnemyAnimationManager();

	location.x += move.x;
}

//描画
void DaggerEnemy::Draw() const
{
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
			}
			else if (location.x <= player->GetCenterLocation().x)
			{
				//右向き
				direction.x = DIRECTION_RIGHT;
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

//パトロール処理
void DaggerEnemy::EnemyPatrol()
{
	//発見出来ていない場合
	if (isFind == false)
	{
		//左向き
		if (direction.x == DIRECTION_LEFT)
		{
			move.x = 0.f;
		}
	}
}

//攻撃準備
void DaggerEnemy::AttackStandBy()
{
}

//攻撃開始
void DaggerEnemy::AttackStart()
{
}

//攻撃終了
void DaggerEnemy::AttackEnd()
{
}

//アニメーションマネージャー
void DaggerEnemy::EnemyAnimationManager()
{
}

//パトロールアニメーション
void DaggerEnemy::PatrolAnim()
{
}

//攻撃準備時のアニメーション(短剣装備中)
void DaggerEnemy::DaggerAttackStandByAnim()
{
}
//攻撃準備時のアニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackStandByAnim()
{
}

//攻撃開始アニメーション(短剣装備あり)
void DaggerEnemy::DaggerAttackStartAnim()
{
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

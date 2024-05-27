#include "DaggerEnemy.h"
#include "../../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
DaggerEnemy::DaggerEnemy():drawnSword(false)
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
	location = { 500,GROUND_LINE - area.height };

	//武器の種類：短剣
	weaponType = Weapon::Dagger;
	enemyType = EnemyType::DaggerEnemy;

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

	//パトロールカウンターの初期設定
	patrolCounter = 0.f;

	//daggerクラスの生成
	dagger = new Dagger;

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
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(FPS * 0.5);
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

	//アニメーション処理
	EnemyAnimationManager();

	//画面端を越えない
	DontCrossBorder();

	location.x += move.x;
}

//描画
void DaggerEnemy::Draw() const
{
	DrawBoxAA(GetMinScreenLocation().x, GetMinScreenLocation().y, 
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,0x00ff00, TRUE, 1.0f);

	DrawFormatString(500, 600, 0xffff00, "%lf PatrolCounter", patrolCounter);
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
	dagger->Attack(this);
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

#include "DaggerEnemy.h"
#include "../Player/Player.h"
#include "../../Camera/Camera.h"

//コンストラクタ
DaggerEnemy::DaggerEnemy(float x, float y) :drawnSword(false), dagger(nullptr), daggerEnemyAnimNumber{(0)},
daggerEnemyAnim{NULL},enemyAnimInterval(0),correctLocX(0.f),correctLocY(0.f),animTurnFlg(TRUE),
animCountDown(false),attackEndCount(0),canAttack(false),clawCollisionBox(nullptr),didAttack(false),
onlyOnce(false),locYCorrect(0)
{
	//表示座標{ x , y }
	location = { x,y };
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
	area = { 70.f,80.f };

	//武器の種類：短剣
	weaponType = Weapon::Dagger;
	enemyType = EnemyType::DaggerEnemy;

	//体の向き
	direction.x = DIRECTION_LEFT;

	//体力
	hp = 100;
	//ダメージ
	damage = 8.f;

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
	attackWaitingTime = MAX_ATTACK_TIME;

	//大剣を呼び出す
	clawCollisionBox = new BoxCollision;
	clawCollisionBox->SetArea({ 30,140 });
}

void DaggerEnemy::Finalize()
{
	delete dagger;
	delete clawCollisionBox;
}

//更新処理
void DaggerEnemy::Update()
{
	//ダメージ間隔
	DamageInterval(FPS * 0.2);
	//ノックバックした時の移動処理
	KnockBack(this, FPS * 0.5, knockBackMove);
	//引数に指定した値よりも下方向に行けない
	Landing(WORLD_HEIGHT);

	//敵の状態遷移
	switch (enemyStatus)
	{
		//パトロール処理
	case EnemyStatus::Patrol:
		
		EnemyPatrol();
		break;

		//攻撃準備処理
	case EnemyStatus::AttackStandBy:
		
		AttackStandBy();
		break;

		//攻撃開始処理
	case EnemyStatus::AttackStart:
		
		AttackStart();
		break;
		
		//攻撃終了処理
	case EnemyStatus::AttackEnd:

		AttackEnd();
		break;

		//死亡処理
	case EnemyStatus::Death:

		Death();
		break;

		//ダメージ処理
	case EnemyStatus::Damage:

		Damage();
		break;

	}
	//攻撃範囲更新
	AttackRange();

	//HPが０以下になったら死亡状態にする
	if (hp <= 0)
	{
		//遷移状態を「死亡」にする
		enemyStatus = EnemyStatus::Death;
		isShow = false;
	}

	//アニメーション処理
	EnemyAnimationManager();

	//画面端を越えない
	DontCrossBorder();

	//アニメーションの画像のX座標のずれを修正
	if (animTurnFlg)
	{
		//左向き
		correctLocX = 45.f;
		clawCollisionBox->SetLocationX(GetCenterLocation().x);
	}
	else
	{
		//右向き
		correctLocX = 30.f;
		clawCollisionBox->SetLocationX(GetCenterLocation().x);
	}
	//Y座標の設定
	clawCollisionBox->SetLocationY(location.y - 60.f);
	//カメラ座標の設定
	clawCollisionBox->SetScreenLocation(Camera::ConvertScreenPosition(clawCollisionBox->GetLocation()));


	//短剣の更新処理の呼び出し
	dagger->Update(this);

	oldLocation = location;

}

//描画
void DaggerEnemy::Draw() const
{
	//エネミーの描画
	DrawRotaGraphF(GetMinScreenLocation().x + correctLocX,
		GetMaxScreenLocation().y + correctLocY, 1, 0,
		daggerEnemyAnim[daggerEnemyAnimNumber], TRUE, animTurnFlg);

	//短剣を描画
	dagger->Draw();

	//デバッグ表示する値
#ifdef DEBUG
	DrawFormatString(500, 600, 0xffff00, "%lf PatrolCounter", patrolCounter);
	DrawFormatString(500, 620, 0xffff00, "%d daggerEnemyAnimNumber", daggerEnemyAnimNumber);
	DrawBoxAA(clawCollisionBox->GetMinScreenLocation().x, clawCollisionBox->GetMinScreenLocation().y,
		clawCollisionBox->GetMaxScreenLocation().x, clawCollisionBox->GetMaxScreenLocation().y,
		0xff00ff, FALSE);
	DrawBoxAA
	(
		GetMinScreenLocation().x - 300, GetCenterScreenLocation().y,
		GetMaxScreenLocation().x + 300, GetMaxScreenLocation().y,
		0xffff00, FALSE
	);
#endif
}

//プレイヤーをみつけた？
void DaggerEnemy::FindPlayer(const Player* player)
{
	const bool statusCheck = ((enemyStatus == EnemyStatus::Patrol) || (enemyStatus == EnemyStatus::AttackStandBy));
	//パトロール状態または攻撃準備中でプレイヤーがダメージを受けていない時
	if ( statusCheck && player->GetIsHit() == false)
	{
		//playerが一定の範囲にいるかどうか判定
		if (attackRange[0].x <= player->GetMaxLocation().x &&
			attackRange[0].y <= player->GetMaxLocation().y &&
			player->GetMinLocation().x <= attackRange[1].x &&
			player->GetMinLocation().y <= attackRange[1].y)
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
	/* 条件：武器無し・攻撃準備段階
	プレイヤーがダメージを受けていない状態 */
	if (weaponType == Weapon::None &&
		enemyStatus == EnemyStatus::AttackStandBy &&
		player->GetIsHit() == false)
	{
		SuddenApproachToPlayer(player);
	}
}

void DaggerEnemy::SuddenApproachToPlayer(const Player* player)
{
	float distance;
	//プレイヤーと自身の距離を計算
	distance = abs(player->GetCenterLocation().x - GetCenterLocation().x);

	if (abs(distance) >= 130.f)
	{
		//向いている方向に向かって接近処理を行う
		if (direction.x == DIRECTION_LEFT)
		{
			//画像：左方向
			animTurnFlg = true;
			//速度：5
			move.x = -5.f;
		}
		else if (direction.x == DIRECTION_RIGHT)
		{
			//画像：右方向
			animTurnFlg = false;
			//速度：5
			move.x = 5.f;
		}
	}
	if (abs(distance) <= 130.f)
	{
		canAttack = true;
	}
}

//攻撃の範囲
void DaggerEnemy::AttackRange()
{
	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 300.f;
	attackRange[0].y = GetCenterLocation().y;
	attackRange[1].x = GetMaxLocation().x + 300.f;
	attackRange[1].y = GetMaxLocation().y;
}


//パトロール処理
void DaggerEnemy::EnemyPatrol()
{
	move.x = 0.f;
	//左向き
	if (direction.x == DIRECTION_LEFT)
	{
		patrolCounter -= DAGGER_ENEMY_WALK_SPEED;
		//左に200進んだら右向きにする
		if (patrolCounter <= -80.f)
		{
			//右向き
			direction.x = DIRECTION_RIGHT;
			//画像反転OFF
			animTurnFlg = false;
		}
	}
	//右向き
	else if (direction.x == DIRECTION_RIGHT)
	{
		patrolCounter += DAGGER_ENEMY_WALK_SPEED;
		//右に200進んだら左向きにする
		if (patrolCounter >= 80.f)
		{
			//左向き
			direction.x = DIRECTION_LEFT;
			//画像反転ON
			animTurnFlg = true;
		}
	}

	//プレイヤーを見つけたら攻撃準備に入る
	if (isFind)
	{
		//攻撃準備に遷移させる
		enemyStatus = EnemyStatus::AttackStandBy;
		//パトロールカウンターのリセット
		patrolCounter = 0.f;
	}
}

void DaggerEnemy::HitWeapon(ObjectBase* object)
{
	CharaBase* target = static_cast<CharaBase*>(object);

	//攻撃が当たる瞬間
	if (signToAttack)
	{
		//相手がダメージを受けていなくて攻撃が当たった場合
		if (target->GetIsShow() && !target->GetIsHit())
		{
			//相手をノックバックする
			target->SetKnockBackMove(DAGGER_ENEMY_KNOCKBACK);
		}
	}
}

//攻撃準備
void DaggerEnemy::AttackStandBy()
{
	//攻撃準備が完了するまでの間、停止する
	move.x = 0.f;
	//短剣の装備中
	if (weaponType == Weapon::Dagger)
	{
		//短剣を取り出していたら
		if (drawnSword == true)
		{
			//攻撃開始に遷移
			enemyStatus = EnemyStatus::AttackStart;
			daggerEnemyAnimNumber = 13;
		}
	}
	//武器がない場合
	else if (weaponType == Weapon::None)
	{
		//攻撃できる？：Yes
		if (canAttack == true)
		{
			//フラグのリセット
			canAttack = false;
			//攻撃開始に遷移
			enemyStatus = EnemyStatus::AttackStart;
		}
	}
}

//攻撃開始
void DaggerEnemy::AttackStart()
{
	//攻撃の間は動かない
	move.x = 0;

	//短剣を装備している場合
	if (weaponType == Weapon::Dagger)
	{
		//攻撃の瞬間になったら
		if (signToAttack)
		{
			//短剣の攻撃関数を生成
			dagger->Attack(this);
			//攻撃終了に遷移
			enemyStatus = EnemyStatus::AttackEnd;
		}
	}
	//武器がない場合
	if (weaponType == Weapon::None)
	{
		//手を振り上げる動作になったら
		if (daggerEnemyAnimNumber == 12)
		{
			//攻撃の瞬間の合図
			signToAttack = true;
		}
		//攻撃を行った場合、攻撃終了に遷移
		if (didAttack)
		{
			//フラグのリセット
			didAttack = false;
			signToAttack = false;
			//ステータスを攻撃終了に遷移させる
			enemyStatus = EnemyStatus::AttackEnd;
		}
	}

}

//攻撃終了
void DaggerEnemy::AttackEnd()
{
	//移動量を０にする
	move.x = 0;
	//剣を振るい終わっていたら
	if (drawnSword == false)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
	}
	if (weaponType == Weapon::None)
	{
		enemyStatus = EnemyStatus::Patrol;
	}
}

//死亡
void DaggerEnemy::Death()
{
	move.x = 0.f;
}

void DaggerEnemy::Damage()
{
	move.x = 0;
	if (damageAnimCount >= 12)
	{
		signToAttack = false;
		damageAnimCount = 0;
		enemyStatus = EnemyStatus::Patrol;
	}
}

//アニメーションマネージャー
void DaggerEnemy::EnemyAnimationManager()
{
	//アニメーション用のフレームカウント
	enemyAnimInterval++;
	
	//パトロール状態
	if (enemyStatus == EnemyStatus::Patrol)
	{
		PatrolAnim();
	}
	//攻撃準備状態
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		if (weaponType == Weapon::Dagger)
		{
			DaggerEnemyAttackStandByAnim();
		}
		else if (weaponType == Weapon::None)
		{
			WeaponNoneAttackStandByAnim();
		}
	}
	//攻撃開始
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
	//攻撃終了
	if (enemyStatus == EnemyStatus::AttackEnd)
	{
		DaggerAttackEndAnim();
	}
	//死亡時のアニメーション
	if (enemyStatus == EnemyStatus::Death)
	{
		//死亡時のアニメーション
		DaggerEnemyDeathAnim();
	}
	if (enemyStatus == EnemyStatus::Damage)
	{
		DaggerEnemyDamageAnim();
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
void DaggerEnemy::DaggerEnemyAttackStandByAnim()
{
	//attackStartに初めて入った場合の画像番号設定
	if (daggerEnemyAnimNumber <= 6)
	{
		daggerEnemyAnimNumber = 6;
	}
	
	//アニメーション番号を加算する場合の処理
	if (daggerEnemyAnimNumber <= 8)
	{
		daggerEnemyAnimNumber = 8;
	}
	if (daggerEnemyAnimNumber >= 12)
	{
		drawnSword = true;
		daggerEnemyAnimNumber = 8;
	}

	//画像番号の更新
	//画像番号の加算
	if (enemyAnimInterval % 8 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

//攻撃準備時のアニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackStandByAnim()
{
	//0～７番を繰り返し続ける
	if (daggerEnemyAnimNumber>=7)
	{
		daggerEnemyAnimNumber = 0;
	}

	//画像番号の更新
	if (enemyAnimInterval % 6 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

//攻撃開始アニメーション(短剣装備あり)
void DaggerEnemy::DaggerAttackStartAnim()
{
	if (daggerEnemyAnimNumber >= 15)
	{
		signToAttack = true;
	}
	else if (daggerEnemyAnimNumber > 18)
	{
		daggerEnemyAnimNumber = 13;
	}

	if (enemyAnimInterval % 6 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

//攻撃開始アニメーション(短剣装備無し)
void DaggerEnemy::WeaponNoneAttackStartAnim()
{
	if (daggerEnemyAnimNumber <= 8 || daggerEnemyAnimNumber >= 18)
	{
		daggerEnemyAnimNumber = 8;
	}
	else if (daggerEnemyAnimNumber >= 17)
	{
		didAttack = true;
	}
	
	if (enemyAnimInterval % 6 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

//攻撃終了アニメーション(短剣装備あり)
void DaggerEnemy::DaggerAttackEndAnim()
{
	if (daggerEnemyAnimNumber < 34)
	{
		daggerEnemyAnimNumber = 34;
	}
	else if (daggerEnemyAnimNumber >= 39)
	{
		daggerEnemyAnimNumber = 34;
		attackEndCount++;
	}

	//drawnSwordをfalse(この処理が通るとPatrolになる)
	if (attackEndCount >= 3)
	{
		drawnSword = false;
		attackEndCount = 0;
	}

	if (enemyAnimInterval % 7 == 0)
	{
		daggerEnemyAnimNumber++;
	}
}

void DaggerEnemy::DaggerEnemyDeathAnim()
{
	if (daggerEnemyAnimNumber <= 24 || daggerEnemyAnimNumber >= 34)
	{
		daggerEnemyAnimNumber = 24;
	}
	else if (daggerEnemyAnimNumber == 33)
	{
		//死亡した？：yes
		deathFlg = true;
	}

	if (enemyAnimInterval % 9 == 0)
	{
		daggerEnemyAnimNumber++;

		if (!onlyOnce)
		{
			//４フレーム毎に上方向に画像をずらす(地面にめり込まないように)
			location.y -= (locYCorrect);
		}

		if (daggerEnemyAnimNumber >= 29 && daggerEnemyAnimNumber <= 31)
		{
			onlyOnce = false;
			locYCorrect += 2.5f;
		}
		else
		{
			onlyOnce = true;
		}
	}
}

void DaggerEnemy::DaggerEnemyDamageAnim()
{
	//anim番号が18未満であれば18に設定する
	if (daggerEnemyAnimNumber < 18 || daggerEnemyAnimNumber > 23)
	{
		daggerEnemyAnimNumber = 18;
	}

	//アニメーション番号の更新
	if (enemyAnimInterval % 9 == 0)
	{
		daggerEnemyAnimNumber++;
		damageAnimCount++;
	}
}